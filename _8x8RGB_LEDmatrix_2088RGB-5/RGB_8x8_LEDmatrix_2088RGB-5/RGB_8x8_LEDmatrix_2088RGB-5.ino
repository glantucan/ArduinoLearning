
int DATA               = 3;
int DATA_OUTPUT_ENABLE = 4;
int LATCH              = 5;
int CLOCK              = 6;
int RESET              = 7;

int prevRow = 0;
int prevCol = 0;

void setup() 
{
  pinMode(DATA, OUTPUT);
  pinMode(DATA_OUTPUT_ENABLE, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(RESET, OUTPUT);

  digitalWrite(DATA_OUTPUT_ENABLE, LOW);
  digitalWrite(RESET, HIGH); 
  
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(DATA, LOW);
  int anodeBit = 1;
  int redBit = 9;
  long data = 0;
  bitWrite(data, anodeBit, HIGH);
  bitWrite(data, redBit, HIGH);
  shiftOut(DATA, CLOCK, MSBFIRST, data);
  Serial.begin(9600);
  Serial.println(data);
  digitalWrite(LATCH, HIGH);
  
  Serial.begin(9600);
  checkMatrix();
  
 
}

void loop() 
{
//  digitalWrite(CLOCK, LOW);
//  digitalWrite(LATCH, LOW);
//  digitalWrite(DATA, LOW);
//  byte anodeByte = B00000001;
//  byte redByte = B11111101;
//  byte greenByte = B11111111;
//  byte blueByte = B11111111;
//  
//  int 
//  long data = 0;
//  shiftOut(DATA, CLOCK, MSBFIRST, anodeByte);
//  shiftOut(DATA, CLOCK, MSBFIRST, redByte);
//  shiftOut(DATA, CLOCK, MSBFIRST, greenByte);
//  shiftOut(DATA, CLOCK, MSBFIRST, blueByte);
//  digitalWrite(LATCH, HIGH);
//  delay(100);
}

void printBinary(long number, int bitDepth){
  for (int i = 0; i < bitDepth; i++){
    Serial.print(bitRead(number, i) ? "1" : "0" );
  }
  Serial.println();
}

void checkMatrix() {
  byte row = 0;
  byte col = 0;
  byte anode =  B00000000;
  byte red =    B00000000;
  byte green =  B00000000;
  byte blue =   B00000000;
  matrixByteWrite(anode, red, green, blue);

  // Check red leds
  while(true) {
    for (row = 0; row < 8; row++){
      // set common anode row
      if (anode == 0){
        anode++;
      } else if (anode == B10000000){
        anode = 1;
      } else {
        anode = anode << 1;
      }
      red =   B10011101;
      green = B11000111;
      blue =  B11110001;
//      for (col = 0; col < 8; col++) {
//        // set red cathode column 
//        if (red == 0){
//          red++;
//        } else if (red == B10000000){
//          red = 1;
//        } else {
//          red = red << 1;
//        }
//        matrixByteWrite(anode, red, green, blue);
//      }
      matrixByteWrite(anode, red, green, blue);
    }
  }
//  red = 0;
//  
//  // Check blue leds
//  while(millis() < 2000) {
//    for (row = 0; row < 8; row++){
//      // set common anode row
//      if (anode == 0){
//        anode++;
//      } else if (anode == B10000000){
//        anode = 1;
//      } else {
//        anode = anode << 1;
//      }
//      for (col = 0; col < 8; col++) {
//        // set blue cathode column 
//        if (blue == 0){
//          blue++;
//        } else if (blue == B10000000){
//          blue = 1;
//        } else {
//          blue = blue << 1;
//        }
//        matrixByteWrite(anode, red, green, blue);
//      }
//    }
//  }  
//  blue = 0;
//  
//  // Check green leds
//  while(millis() < 3000) {
//    for (row = 0; row < 8; row++){
//      // set common anode row
//      if (anode == 0){
//        anode++;
//      } else if (anode == B10000000){
//        anode = 1;
//      } else {
//        anode = anode << 1;
//      }
//      for (col = 0; col < 8; col++) {
//        // set green cathode column 
//        if (green == 0){
//          green++;
//        } else if (green == B10000000){
//          green = 1;
//        } else {
//          green = green << 1;
//        }
//        matrixByteWrite(anode, red, green, blue);
//      }
//    }
//  }
}

void matrixByteWrite(byte anode, byte red, byte green, byte blue) {
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(DATA, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, anode);
  shiftOut(DATA, CLOCK, MSBFIRST, ~red);
  shiftOut(DATA, CLOCK, MSBFIRST, ~green);
  shiftOut(DATA, CLOCK, MSBFIRST, ~blue);
  digitalWrite(LATCH, HIGH);
}

void setPixelColor(int row, int col, bool red, bool green, bool blue) {
  int anode = B00000001;
  anode = anode << row;
  if (red) {
    int r = B00000001;
    
  }
}

