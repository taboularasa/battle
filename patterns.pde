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
