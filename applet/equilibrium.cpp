#define SerialTimeout 8192
#define TurnLength 18
#define NumPatterns 14

#include "WProgram.h"
void gamesetup();
void setup();
void loop();
void establishCommunication();
void sendCommunication();
void recieveCommunication();
void setUpMatrix();
void loadPatterns();
void word0();
void word1();
void word2();
void word3();
void word4();
void word5();
void word6();
void word7();
void word8();
void word9();
void word10();
void word11();
void word12();
void word13();
void splashScreen();
void waitingFlash();
void outboundFlash();
void inboundFlash();
void markov();
void countInComingSequence();
void buildNewSequence();
unsigned long pause = 75;


//this is for thinking stuff
float transitionTotals[NumPatterns][NumPatterns];
float wordOccurenceSum[NumPatterns];
float transitionProbability[NumPatterns][NumPatterns];


//this is some stuff for communication
byte CommEstablished;
long TimeStamp;
byte MyTurn = 0;
byte i,j; 
byte inByte;
byte inByte1, inByte2;
byte outboundBytes[TurnLength];
byte inboundBytes[TurnLength];
byte timeout;
int8_t temp = 0;
//unsigned long LastTime = millis();
byte k;
void getSerialChar(byte &theChar, byte &timedOut);

//this is stuff for the i/o pins
int NUMPINS = 16;
int ledPins[] = {
  15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};



//this is the display matrix
int matrix[4][4];

//these are patterns to display as "words"
void (*words[14])();
void word0();
void word1();
void word2();
void word3();
void word4();
void word5();
void word6();
void word7();
void word8();
void word9();
void word10();
void word11();
void word12();
void word13();

void gamesetup()
{
  Serial1.flush();
  MyTurn = 0;
  CommEstablished = 0;
  randomSeed(analogRead(0));
  splashScreen();
  //this is for just making random outbound
  for(byte i = 0;i< TurnLength; i++) outboundBytes[i] = random(1,14);  
}


void setup() {
  randomSeed(analogRead(0));
  delay(random(0,1000));
  //this is in protocol
  gamesetup();

  //add patterns to the words array
  loadPatterns();

  //set up the matrix i/o pin addresses
  setUpMatrix();

  //set i/o pins to output
  for (i=0;i<NUMPINS;i++) pinMode(ledPins[i], OUTPUT);

  //start up serial ports
  Serial.begin(1200);
  Serial1.begin(1200);
  splashScreen();
}

void loop(){
  LoopStart:
  
  if (CommEstablished == 0){
    establishCommunication();
  }
  else
  {
    if (MyTurn == 1)
    {
      sendCommunication();
    } 
    else
    { 
      recieveCommunication();
    }
  }
}


void establishCommunication()
{
  j = 0;

  Serial1.flush();
  TimeStamp = millis();
  while (CommEstablished == 0)
  {
    waitingFlash();
    if (Serial1.available() > 0) 
    {
      inByte = Serial1.read();
      Serial1.flush();
      if (inByte == 'R')
      {
        Serial1.print('B', BYTE);     // We will go second
        CommEstablished = 1; 
      }
      if (inByte == 'B')
      {
        Serial1.print('P', BYTE);     // We will go First
        CommEstablished = 1;
        MyTurn = 1;
      }      

    }
    else
    {
      if((millis() - TimeStamp) > 500)
      {
        Serial1.flush();
        Serial1.print('R', BYTE);     // Attempt to initiate communication 
      }
    }
  }
}//end of establishCommunication()


void sendCommunication()
{
  Serial1.flush();
  byte communicationTries = 0;
  while (Serial1.available() == 0)
  {
    Serial.print("stuck in here ");
    Serial.println(communicationTries,DEC);
    Serial1.print('F', BYTE);   // Initiate Communication Sequence
    for(byte i=0; i < TurnLength; i++) Serial1.print(outboundBytes[i], BYTE); //sending the array of BYTES that was just displayed
    Serial1.print('f', BYTE);   //End Communication Sequence    
    delay(50);
    if(communicationTries >= 30)
    {
      Serial.print("i try to do game setup");
      communicationTries = 0;
      gamesetup();
      return;
    }
    communicationTries++;

  }

  //here's how we listen to see if our message was heard:
  inByte = Serial1.read();        
  if (inByte == 'H')
  {
    k = 0;    
    while (k < 250)
    {   
      if (Serial1.available() > 0)
        break; 
      delay(1);
      k++;
    }
    //here's their response
    inByte2 = Serial1.read();  
    Serial1.flush();
  }
  inboundFlash();       
  MyTurn = 0;
  Serial1.flush();
}//end of sendCommunication()


void recieveCommunication()
{
  if (Serial1.available() > 0) 
  {
    inByte = Serial1.read();        
    if (inByte == 'F')
    {
      timeout = 0; 
      //reading the incoming BYTES and storing them
      for(byte i=0; i < TurnLength; i++) inboundBytes[i] = 255;
      for(byte i=0; i < TurnLength; i++) getSerialChar(inboundBytes[i], timeout);
      getSerialChar(inByte, timeout);

      // Now check the numbers for sanity:
      byte SyntaxOK = 1;
      for(byte i=0; i < TurnLength; i++) if(inboundBytes[i] > NumPatterns-1) SyntaxOK = 0;
      if ((SyntaxOK == 0) || (timeout))
      {
        Serial1.flush();
        Serial.println("timed out or syntax not ok");
      }

      // Data recieved successfully
      else if (inByte == 'f')
      {   
        markov();
        for(byte i=0; i < TurnLength; i++) words[outboundBytes[i]]();
        //send back to say you got it
        Serial1.print('H', BYTE);   // Here's the start flag
        Serial1.print('1', BYTE);   // heres the message
        Serial1.print('h', BYTE);   // Here's the end flag


        outboundFlash();
        MyTurn = 1;
      }
    }
    else
    {
      //Didn't catch the start of the package so I'll wait for the next one
      Serial1.flush();
    }// End " if (inByte == 'F') else"
  }
  else
  {
    delay(13);
  }
}


void getSerialChar(byte &theByte, byte &timedOut)
{ 
  if (timedOut == 0)
  {
    unsigned int i = 0;
    byte WaitForData = 1;  

    while (WaitForData)   // give up if we don't get data in a certain amount of time
    {
      if (Serial1.available() > 0)
      {
        WaitForData = 0; 
        theByte = Serial1.read();
      } 
      else if (++i > SerialTimeout)
      {
        WaitForData = 0;  
        timedOut = 1;
      }
    }   // end "while (WaitForData)" 
  }
  return; 
}

////////SETUP FUNCTIONS

void setUpMatrix()
{
  matrix[0][0]= 27;
  matrix[1][0]= 28;
  matrix[2][0]= 29;
  matrix[3][0]= 30;
  matrix[0][1]= 23;
  matrix[1][1]= 24;
  matrix[2][1]= 25;
  matrix[3][1]= 26;
  matrix[0][2]= 19;
  matrix[1][2]= 20;
  matrix[2][2]= 21;
  matrix[3][2]= 22;
  matrix[0][3]= 15;
  matrix[1][3]= 16;
  matrix[2][3]= 17;
  matrix[3][3]= 18;
}

void loadPatterns()
{
  //add patterns to the words array
  words[0] = &word0;
  words[1] = &word1;
  words[2] = &word2;
  words[3] = &word3;
  words[4] = &word4;
  words[5] = &word5;
  words[6] = &word6;
  words[7] = &word7;
  words[8] = &word8;
  words[9] = &word9;
  words[10] = &word10;
  words[11] = &word11;
  words[12] = &word12;
  words[13] = &word13;
}


/////////MAIN PATTERNS

void word0(){
  digitalWrite(matrix[1][3], HIGH);
  digitalWrite(matrix[2][2], HIGH);
  digitalWrite(matrix[3][1], HIGH);
  delay(pause);
  digitalWrite(matrix[1][3], LOW);
  digitalWrite(matrix[2][2], LOW);
  digitalWrite(matrix[3][1], LOW);
  delay(pause);
}

void word1(){
  digitalWrite(matrix[1][0], HIGH);
  digitalWrite(matrix[2][1], HIGH);
  digitalWrite(matrix[3][2], HIGH);
  delay(pause);
  digitalWrite(matrix[1][0], LOW);
  digitalWrite(matrix[2][1], LOW);
  digitalWrite(matrix[3][2], LOW);
  delay(pause);
}

void word2(){
  digitalWrite(matrix[0][0], HIGH);
  digitalWrite(matrix[1][0], HIGH);
  digitalWrite(matrix[2][3], HIGH);
  digitalWrite(matrix[3][3], HIGH);
  delay(pause);
  digitalWrite(matrix[0][0], LOW);
  digitalWrite(matrix[1][0], LOW);
  digitalWrite(matrix[2][3], LOW);
  digitalWrite(matrix[3][3], LOW);
  delay(pause);
}

void word3(){
  digitalWrite(matrix[0][0], HIGH);
  digitalWrite(matrix[0][1], HIGH);
  digitalWrite(matrix[1][0], HIGH);
  digitalWrite(matrix[1][1], HIGH);
  delay(pause);
  digitalWrite(matrix[0][0], LOW);
  digitalWrite(matrix[0][1], LOW);
  digitalWrite(matrix[1][0], LOW);
  digitalWrite(matrix[1][1], LOW);
  delay(pause);
}

void word4(){
  digitalWrite(matrix[0][2], HIGH);
  digitalWrite(matrix[0][3], HIGH);
  digitalWrite(matrix[1][2], HIGH);
  digitalWrite(matrix[1][3], HIGH);
  delay(pause);
  digitalWrite(matrix[0][2], LOW);
  digitalWrite(matrix[0][3], LOW);
  digitalWrite(matrix[1][2], LOW);
  digitalWrite(matrix[1][3], LOW);
  delay(pause);
}

void word5(){
  digitalWrite(matrix[2][0], HIGH);
  digitalWrite(matrix[2][1], HIGH);
  digitalWrite(matrix[3][0], HIGH);
  digitalWrite(matrix[3][1], HIGH);
  delay(pause);
  digitalWrite(matrix[2][0], LOW);
  digitalWrite(matrix[2][1], LOW);
  digitalWrite(matrix[3][0], LOW);
  digitalWrite(matrix[3][1], LOW);
  delay(pause);
}

void word6(){
  digitalWrite(matrix[2][2], HIGH);
  digitalWrite(matrix[2][3], HIGH);
  digitalWrite(matrix[3][2], HIGH);
  digitalWrite(matrix[3][3], HIGH);
  delay(pause);
  digitalWrite(matrix[2][2], LOW);
  digitalWrite(matrix[2][3], LOW);
  digitalWrite(matrix[3][2], LOW);
  digitalWrite(matrix[3][3], LOW);
  delay(pause);
}

void word7(){
  digitalWrite(matrix[0][1], HIGH);
  digitalWrite(matrix[0][2], HIGH);
  digitalWrite(matrix[1][1], HIGH);
  digitalWrite(matrix[1][2], HIGH);
  digitalWrite(matrix[2][1], HIGH);
  digitalWrite(matrix[2][2], HIGH);
  digitalWrite(matrix[3][1], HIGH);
  digitalWrite(matrix[3][2], HIGH);
  delay(pause);
  digitalWrite(matrix[0][1], LOW);
  digitalWrite(matrix[0][2], LOW);
  digitalWrite(matrix[1][1], LOW);
  digitalWrite(matrix[1][2], LOW);
  digitalWrite(matrix[2][1], LOW);
  digitalWrite(matrix[2][2], LOW);
  digitalWrite(matrix[3][1], LOW);
  digitalWrite(matrix[3][2], LOW);
  delay(pause);
}

void word8(){
  digitalWrite(matrix[1][0], HIGH);
  digitalWrite(matrix[1][1], HIGH);
  digitalWrite(matrix[1][2], HIGH);
  digitalWrite(matrix[1][3], HIGH);
  digitalWrite(matrix[2][0], HIGH);
  digitalWrite(matrix[2][1], HIGH);
  digitalWrite(matrix[2][2], HIGH);
  digitalWrite(matrix[2][3], HIGH);
  delay(pause);
  digitalWrite(matrix[1][0], LOW);
  digitalWrite(matrix[1][1], LOW);
  digitalWrite(matrix[1][2], LOW);
  digitalWrite(matrix[1][3], LOW);
  digitalWrite(matrix[2][0], LOW);
  digitalWrite(matrix[2][1], LOW);
  digitalWrite(matrix[2][2], LOW);
  digitalWrite(matrix[2][3], LOW);
  delay(pause);
}

void word9(){
  digitalWrite(matrix[0][3], HIGH);
  digitalWrite(matrix[1][3], HIGH);
  digitalWrite(matrix[2][0], HIGH);
  digitalWrite(matrix[3][0], HIGH);
  delay(pause);
  digitalWrite(matrix[0][3], LOW);
  digitalWrite(matrix[1][3], LOW);
  digitalWrite(matrix[2][0], LOW);
  digitalWrite(matrix[3][0], LOW);
  delay(pause);
}

void word10(){
  digitalWrite(matrix[0][0], HIGH);
  digitalWrite(matrix[1][1], HIGH);
  digitalWrite(matrix[2][2], HIGH);
  digitalWrite(matrix[3][3], HIGH);
  delay(pause);
  digitalWrite(matrix[0][0], LOW);
  digitalWrite(matrix[1][1], LOW);
  digitalWrite(matrix[2][2], LOW);
  digitalWrite(matrix[3][3], LOW);
  delay(pause);
}

void word11(){
  digitalWrite(matrix[0][3], HIGH);
  digitalWrite(matrix[1][2], HIGH);
  digitalWrite(matrix[2][1], HIGH);
  digitalWrite(matrix[3][0], HIGH);
  delay(pause);
  digitalWrite(matrix[0][3], LOW);
  digitalWrite(matrix[1][2], LOW);
  digitalWrite(matrix[2][1], LOW);
  digitalWrite(matrix[3][0], LOW);
  delay(pause);
}

void word12(){
  digitalWrite(matrix[0][1], HIGH);
  digitalWrite(matrix[1][2], HIGH);
  digitalWrite(matrix[2][3], HIGH);
  delay(pause);
  digitalWrite(matrix[0][1], LOW);
  digitalWrite(matrix[1][2], LOW);
  digitalWrite(matrix[2][3], LOW);
  delay(pause);
}

void word13(){
  digitalWrite(matrix[0][2], HIGH);
  digitalWrite(matrix[1][1], HIGH);
  digitalWrite(matrix[2][0], HIGH);
  delay(pause);
  digitalWrite(matrix[0][2], LOW);
  digitalWrite(matrix[1][1], LOW);
  digitalWrite(matrix[2][0], LOW);
  delay(pause);
}




///EXTRA PATTERNS

void splashScreen(){
  digitalWrite(matrix[0][0], HIGH);
  digitalWrite(matrix[0][1], HIGH);
  digitalWrite(matrix[0][2], HIGH);
  digitalWrite(matrix[0][3], HIGH);
  delay(60);
  digitalWrite(matrix[0][0], LOW);
  digitalWrite(matrix[0][1], LOW);
  digitalWrite(matrix[0][2], LOW);
  digitalWrite(matrix[0][3], LOW);
  delay(60);
  digitalWrite(matrix[1][0], HIGH);
  digitalWrite(matrix[1][1], HIGH);
  digitalWrite(matrix[1][2], HIGH);
  digitalWrite(matrix[1][3], HIGH);
  delay(60);
  digitalWrite(matrix[1][0], LOW);
  digitalWrite(matrix[1][1], LOW);
  digitalWrite(matrix[1][2], LOW);
  digitalWrite(matrix[1][3], LOW);
  delay(60);
  digitalWrite(matrix[2][0], HIGH);
  digitalWrite(matrix[2][1], HIGH);
  digitalWrite(matrix[2][2], HIGH);
  digitalWrite(matrix[2][3], HIGH);
  delay(60);
  digitalWrite(matrix[2][0], LOW);
  digitalWrite(matrix[2][1], LOW);
  digitalWrite(matrix[2][2], LOW);
  digitalWrite(matrix[2][3], LOW);
  delay(60);
  digitalWrite(matrix[3][0], HIGH);
  digitalWrite(matrix[3][1], HIGH);
  digitalWrite(matrix[3][2], HIGH);
  digitalWrite(matrix[3][3], HIGH);
  delay(60);
  digitalWrite(matrix[3][0], LOW);
  digitalWrite(matrix[3][1], LOW);
  digitalWrite(matrix[3][2], LOW);
  digitalWrite(matrix[3][3], LOW);
  delay(60);
}


void waitingFlash(){
  digitalWrite(matrix[0][0], HIGH);
  delay(320);
  digitalWrite(matrix[0][0], LOW);
  delay(320);
}

void outboundFlash(){
  delay(500);
  digitalWrite(matrix[1][1], HIGH);
  digitalWrite(matrix[1][2], HIGH);
  digitalWrite(matrix[2][1], HIGH);
  digitalWrite(matrix[2][2], HIGH);
  delay(120);
  digitalWrite(matrix[1][1],  LOW);
  digitalWrite(matrix[1][2],  LOW);
  digitalWrite(matrix[2][1],  LOW);
  digitalWrite(matrix[2][2], LOW);
  delay(200);
  digitalWrite(matrix[0][0], HIGH);
  digitalWrite(matrix[0][1], HIGH);
  digitalWrite(matrix[0][2], HIGH);
  digitalWrite(matrix[0][3], HIGH);
  digitalWrite(matrix[1][0], HIGH);
  digitalWrite(matrix[1][3], HIGH);
  digitalWrite(matrix[2][0], HIGH);
  digitalWrite(matrix[2][3], HIGH);
  digitalWrite(matrix[3][0], HIGH);
  digitalWrite(matrix[3][1], HIGH);
  digitalWrite(matrix[3][2], HIGH);
  digitalWrite(matrix[3][3], HIGH);
  delay(120);
  digitalWrite(matrix[0][0], LOW);
  digitalWrite(matrix[0][1], LOW);
  digitalWrite(matrix[0][2], LOW);
  digitalWrite(matrix[0][3], LOW);
  digitalWrite(matrix[1][0], LOW);
  digitalWrite(matrix[1][3], LOW);
  digitalWrite(matrix[2][0], LOW);
  digitalWrite(matrix[2][3], LOW);
  digitalWrite(matrix[3][0], LOW);
  digitalWrite(matrix[3][1], LOW);
  digitalWrite(matrix[3][2], LOW);
  digitalWrite(matrix[3][3], LOW);
  delay(500);
}

void inboundFlash(){
  delay(500);
  digitalWrite(matrix[0][0], HIGH);
  digitalWrite(matrix[0][1], HIGH);
  digitalWrite(matrix[0][2], HIGH);
  digitalWrite(matrix[0][3], HIGH);
  digitalWrite(matrix[1][0], HIGH);
  digitalWrite(matrix[1][3], HIGH);
  digitalWrite(matrix[2][0], HIGH);
  digitalWrite(matrix[2][3], HIGH);
  digitalWrite(matrix[3][0], HIGH);
  digitalWrite(matrix[3][1], HIGH);
  digitalWrite(matrix[3][2], HIGH);
  digitalWrite(matrix[3][3], HIGH);
  delay(120);
  digitalWrite(matrix[0][0], LOW);
  digitalWrite(matrix[0][1], LOW);
  digitalWrite(matrix[0][2], LOW);
  digitalWrite(matrix[0][3], LOW);
  digitalWrite(matrix[1][0], LOW);
  digitalWrite(matrix[1][3], LOW);
  digitalWrite(matrix[2][0], LOW);
  digitalWrite(matrix[2][3], LOW);
  digitalWrite(matrix[3][0], LOW);
  digitalWrite(matrix[3][1], LOW);
  digitalWrite(matrix[3][2], LOW);
  digitalWrite(matrix[3][3], LOW);
  delay(200);
    digitalWrite(matrix[1][1], HIGH);
  digitalWrite(matrix[1][2], HIGH);
  digitalWrite(matrix[2][1], HIGH);
  digitalWrite(matrix[2][2], HIGH);
  delay(120);
  digitalWrite(matrix[1][1],  LOW);
  digitalWrite(matrix[1][2],  LOW);
  digitalWrite(matrix[2][1],  LOW);
  digitalWrite(matrix[2][2], LOW);
  delay(500);
}

void markov()
{
  countInComingSequence();
  buildNewSequence();
}

void countInComingSequence()
{
  //we need to know how many times each pattern appears so we can divide transitions by it later
  //first clear out wordOccurenceSum
  for(byte i=0; i < NumPatterns; i++) wordOccurenceSum[i] = 0;
  
  //then add up the number of times each pattern appears
  for(byte i=0; i < TurnLength; i++) wordOccurenceSum[inboundBytes[i]]++;

  //this is to clear out transitionTotals array
  for(byte i=0; i < NumPatterns; i++)
  {
    for(byte j=0; j < NumPatterns; j++)
    {
      transitionTotals[i][j] = 0;
    }
  }

  //this keeps track of how many times each transition occurs
  for(byte i=0; i < TurnLength; i++)
  {
    transitionTotals[inboundBytes[i]][inboundBytes[i+1]]++;
  }

  //lets empty out the transitionProbability array so we can make new stats
  for(byte i=0;i<NumPatterns;i++)
  {
    for(byte j = 0; j<NumPatterns;j++)
    {
      transitionProbability[i][j] = 0.00;
    }
  }

  //now we need to take the number of times a transition happended and divide it by
  //the number of times an inital state appears in the sequence to get the probability
  //of that transition happening
  for(byte i=0; i < NumPatterns; i++)
  { 
    //this is special case for the beginning the iteration   
    float tempA = wordOccurenceSum[i];
    float tempB = transitionTotals[i][0];    
    transitionProbability[i][0] = tempB/tempA;

    for(byte j=1; j < NumPatterns; j++)
    {  
      tempA = wordOccurenceSum[i];
      tempB = transitionTotals[i][j];

      //add up the percentage for every step in the iteration
      transitionProbability[i][j] = transitionProbability[i][j - 1] + tempB/tempA;
    }
  } 
}

void buildNewSequence()
{ 

  //this is to start out with a random outbound:
  for(byte i = 0;i< TurnLength; i++) outboundBytes[i] = random(0,14);
  
  //start the sequence with the last position of incomming bytes
  outboundBytes[0] = inboundBytes[random(0,13)];
  
  //for the second position and on look at the last position and randomly choose from the most probable transitions
  for(byte i=1; i< TurnLength; i++)
  {
    randomSeed(analogRead(0));
    float rnd = random(2,11);
    rnd = rnd/10;
    for (byte j = 0; j < NumPatterns; j++)
    {
      if (rnd <= transitionProbability[outboundBytes[i-1]][j])
      {
        //throw a monkey wrench in the zero bias :(
        if(j==0) j = random(0,5);
        outboundBytes[i] = j;
        break;
      }
    }
  }
  boolean different = false;
  for(byte i=0; i< TurnLength; i++)
  {
    if(outboundBytes[i]!=inboundBytes[i]) different = true;
  }
  if (different == false)
  {
    //this means that I loose so restart the game
    splashScreen();
    splashScreen();
    delay(500);

    //start over by making a new random sequence for us to guess
    for(byte i = 0;i< TurnLength; i++) outboundBytes[i] = random(1,14);
  }
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

