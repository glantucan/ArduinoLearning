#include <SPI.h>
//const byte CLOCK = 2; 
//const byte MOSI = 4;
// When using SPI library, the pings for MOSI and CLOCK are 11 ad 13 respectively (UNO and NANO)
const byte ENABLE = 10;



static uint8_t data[4] = {0x0, 0x0, 0x0, 0x0};
static uint8_t i = 1;

void heartbig()
{
  int j;
  int x = 2;
  static uint8_t heart[8] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
  for ( j = 0; j < 8; j++)
  {
    data[0] = ~heart[j];
    data[2] = 0xFF;
    data[1] = 0xFF;
    data[3] = 0x01 << j ;
    digitalWrite(ENABLE, LOW);
    SPI.transfer(data[0]);
    SPI.transfer(data[2]);
    SPI.transfer(data[1]);
    SPI.transfer(data[3]);
    digitalWrite(ENABLE, HIGH);
    delay(x);
  }
};

void heartsmall()
{
  int j;
  int x = 2;
  static uint8_t heart[8] = {0x00, 0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00};
  for ( j = 0; j < 8; j++)
  {
    data[0] = ~heart[j];
    data[2] = 0xFF;
    data[1] = 0xFF;
    data[3] = 0x01 << j ;
    digitalWrite(ENABLE, LOW);
    SPI.transfer(data[0]);
    SPI.transfer(data[2]);
    SPI.transfer(data[1]);
    SPI.transfer(data[3]);
    digitalWrite(ENABLE, HIGH);
    delay(x);
  }
};

void matrixoff()
{
  int j;
  int x = 2;
  static uint8_t heart[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for ( j = 0; j < 8; j++)
  {
    data[0] = ~heart[j];
    data[2] = 0xFF;
    data[1] = 0xFF;
    data[3] = 0x01 << j ;
    digitalWrite(ENABLE, LOW);
    SPI.transfer(data[0]);
    SPI.transfer(data[2]);
    SPI.transfer(data[1]);
    SPI.transfer(data[3]);
    digitalWrite(ENABLE, HIGH);
    delay(x);
  }

};

void setup() {
  pinMode(ENABLE, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(15000000, LSBFIRST, SPI_MODE1));
  //SPI.begin();
  int j;
  int interval = 0;
  
  static uint8_t heart[8] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
  static uint8_t heart_s[8] = {0x00, 0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00};
  static uint8_t data[4] = {0x0, 0x0, 0x0, 0x0};
  
  while (true){
    for ( j = 0; j < 8; j++)
    {
      data[0] = ~heart[j];
      data[1] = heart_s[j];
      data[2] = heart[j];
      data[3] = 0x01 << j ;
      digitalWrite(ENABLE, LOW);
      SPI.transfer(data[0]);
      SPI.transfer(255);
      SPI.transfer(255);
      SPI.transfer(data[3]);
      digitalWrite(ENABLE, HIGH);
      delayMicroseconds(100);
      
      digitalWrite(ENABLE, LOW);
      SPI.transfer(255);
      SPI.transfer(data[1]);
      SPI.transfer(255);
      SPI.transfer(data[3]);
      digitalWrite(ENABLE, HIGH);
      delayMicroseconds(50);
      
      digitalWrite(ENABLE, LOW);
      SPI.transfer(255);
      SPI.transfer(255);
      SPI.transfer(data[2]);
      SPI.transfer(data[3]);
      digitalWrite(ENABLE, HIGH);
      
      delayMicroseconds(20);
    }
    delay(interval);
   }
}

void loop() {
/*
  int m = 10;
  for ( m = 10; m > 0; m--) {
    heartbig();
  };
  matrixoff();
  delay(1000);
  for ( m = 10; m > 0; m--) {
    heartsmall();
  };
  matrixoff();
  delay(1000);
*/
}
