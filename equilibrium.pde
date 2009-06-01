#define SerialTimeout 8192
#define TurnLength 18
#define NumPatterns 14

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

