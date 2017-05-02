

int DATA               = 3;
int DATA_OUTPUT_ENABLE = 4;
int LATCH              = 5;
int CLOCK              = 6;
int RESET              = 7;
int R_OE               = 9;
int G_OE               = 10;
int B_OE               = 11;

long lineScan = 0;
long counter = 0;
byte Screen[8][8] = {{7,7,7,7,7,7,7,7},
                     {7,7,7,7,7,7,7,7},
                     {7,7,7,7,7,7,7,7},
                     {7,7,7,7,7,7,7,7},
                     {7,7,7,7,7,7,7,7},
                     {7,7,7,7,7,7,7,7},
                     {7,7,7,7,7,7,7,7},
                     {7,7,7,7,7,7,7,7}};
void setup() {
  // put your setup code here, to run once:
  pinMode(DATA, OUTPUT);
  pinMode(DATA_OUTPUT_ENABLE, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(R_OE, OUTPUT);
  pinMode(G_OE, OUTPUT);
  pinMode(B_OE, OUTPUT);
  digitalWrite(DATA_OUTPUT_ENABLE, LOW);
  digitalWrite(R_OE, LOW);
  digitalWrite(G_OE, LOW);
  digitalWrite(B_OE, LOW);
  digitalWrite(RESET, HIGH); 
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(DATA, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  counter += millis();
  //if(counter > 1) {
   // counter = 0;
//    byte rnd_col = random(0, 8);
//    byte rnd_row = random(0, 8);
//    Screen[rnd_row][rnd_col] = random(0, 8);
    sendDataFromArray(lineScan%8);
  //}
  lineScan++;
}



void sendBit(uint8_t aData){
  digitalWrite(DATA,  aData);  
  digitalWrite(CLOCK, HIGH);
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA,  LOW);  
}


void sendDataFromArray(byte lineIndex){
  
  //byte lineIndex;
  byte rowIndex;
  //for(lineIndex = 0; lineIndex < 8; lineIndex++){
    
    //Set Anode Line
    for(rowIndex = 0; rowIndex < 8; rowIndex++){
      if (lineIndex == rowIndex){
        sendBit(HIGH);
      } else {
        sendBit(LOW);
      }
    }

    //Set Green Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++){
      if ((Screen[lineIndex][rowIndex] & 1) == 0){
        sendBit(HIGH);
      } else {
        sendBit(LOW);
      }
    }

    //Set Red Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++){
      if ((Screen[lineIndex][rowIndex] & 2) == 0){
        sendBit(HIGH);
      } else {
        sendBit(LOW);
      }
    }

    //Set Blue Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++){
      if ((Screen[lineIndex][rowIndex] & 4) == 0){
        sendBit(HIGH);
      } else {
        sendBit(LOW);
      }
    }

    //Send data to output
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
    
    delayMicroseconds(1250);
   
    digitalWrite(RESET, LOW);
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
    
    digitalWrite(RESET, HIGH);
     //delay(500);
  //}
}
