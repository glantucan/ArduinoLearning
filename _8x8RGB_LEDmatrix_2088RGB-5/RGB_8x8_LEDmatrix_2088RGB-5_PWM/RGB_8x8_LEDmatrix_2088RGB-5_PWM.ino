
#include <Wire.h>
#include <PCA9685.h>
#if F_CPU >= 16000000
#define I2C_FASTMODE 1                  // Running a 16MHz processor allows us to use I2C fast mode
#endif
PCA9685 pwmController; 

//#include <Adafruit_PWMServoDriver.h>
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

int DATA               = 4;
int DATA_OUTPUT_ENABLE = 3;
int LATCH              = 5;
int CLOCK              = 6;
int RESET              = 7;

uint16_t red[3] = {4095 - 255*16, 4095 -   0*16, 4095 -   0*16};
uint16_t gre[3] = {4095 -   0*16, 4095 - 255*16, 4095 -   0*16};
uint16_t blu[3] = {4095 -   0*16, 4095 -   0*16, 4095 - 255*16};
uint16_t ora[3] = {4095 - 255*16, 4095 -  50*16, 4095 -   0*16};
uint16_t pin[3] = {4095 - 255*16, 4095 -  40*16, 4095 -  80*16};
uint16_t tur[3] = {4095 -   0*16, 4095 - 180*16, 4095 - 190*16};
uint16_t bro[3] = {4095 - 180*16, 4095 -  10*16, 4095 -   2*16};
uint16_t yel[3] = {4095 - 255*16, 4095 -  90*16, 4095 -   5*16};
uint16_t gra[3] = {4095 - 160*16, 4095 -  90*16, 4095 -  50*16};
uint16_t pur[3] = {4095 - 200*16, 4095 -   0*16, 4095 -  70*16};
uint16_t whi[3] = {4095 -   0*16, 4095 - 255*16, 4095 -   0*16};
uint16_t bla[3] = {4095 -   0*16, 4095 -   0*16, 4095 -   0*16};


uint16_t *Screen[8][8] = {{red, red, gre, gre, blu, blu, ora, ora},
                     {red, red, gre, gre, blu, blu, ora, ora},
                     {pin, pin, tur, tur, bro, bro, yel, yel},
                     {pin, pin, tur, tur, bro, bro, yel, yel},
                     {gra, gra, pur, pur, whi, whi, whi, whi},
                     {gra, gra, pur, pur, whi, whi, whi, whi},
                     {red, red, gre, gre, blu, blu, ora, ora},
                     {red, red, gre, gre, blu, blu, ora, ora}};
                        
void setup() {
  // put your setup code here, to run once:
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

//  pwm.begin();
//  pwm.setPWMFreq(1600);
//  pwm.setPWM(0, 255*16, 4095);
//  pwm.setPWM(1, 255*16, 4095);
//  pwm.setPWM(2, 255*16, 4095);


  Wire.begin();                       // Wire must be started first
  Wire.setClock(400000);              // Supported baud rates are 100kHz, 400kHz, and 1000kHz

  pwmController.resetDevices();       // Software resets all PCA9685 devices on Wire line

  pwmController.init(B00000000);        // Address pins A5-A0 set to B000000
  pwmController.setPWMFrequency(1500); // Default is 200Hz, supports 24Hz to 1526Hz

  
  
}

void loop() {
  screenUpdate();
}

void sendBit(uint8_t aData){
  digitalWrite(DATA,  aData);  
  digitalWrite(CLOCK, HIGH);
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA,  LOW);  
}


void screenUpdate(){
  byte zero = B00000000;
  byte one =  B00000001;
  
  byte anode = one;

  
  for (byte row = 0; row < 8; row++) {
    
    
    byte red = one;
    byte green = one;
    byte blue = one;
    
    for (byte col = 0; col < 8; col++) {
//      pwm.set3PWMon(0, Screen[col][row][0], 1, Screen[col][row][1], 2, Screen[col][row][2]);
//      pwm.setPWM(0, Screen[col][row][0], 4095);
//      pwm.setPWM(1, Screen[col][row][1], 4095);
//      pwm.setPWM(2, Screen[col][row][2], 4095);
      pwmController.setChannelPWM(0, Screen[col][row][0]);
      pwmController.setChannelPWM(1, Screen[col][row][1]);
      pwmController.setChannelPWM(2, Screen[col][row][2]);
//      pwmController.setChannelsPWM(0, 3, Screen[col][row]);
      shiftOut(DATA, CLOCK, MSBFIRST, anode);
      shiftOut(DATA, CLOCK, MSBFIRST, ~red);
      shiftOut(DATA, CLOCK, MSBFIRST, ~green);
      shiftOut(DATA, CLOCK, MSBFIRST, ~blue);
      digitalWrite(LATCH, HIGH);
      digitalWrite(LATCH, LOW);
      //delayMicroseconds(20000);
      //digitalWrite(RESET, LOW);
      //digitalWrite(RESET, HIGH);
      red = red << 1;
      green = green << 1;
      blue = blue << 1;
    }
    anode = anode << 1;
    
    
  }
}
