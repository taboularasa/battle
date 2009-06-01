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
