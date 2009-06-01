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
