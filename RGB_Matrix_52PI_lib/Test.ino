

/*#include <SPI.h> 
// When using SPI library, the pings for MOSI and CLOCK 
// are 11 ad 13 respectively (UNO and NANO, MISO is 12)

#define SS 10   // SS is the Slave Select line. 
                      // The pin used to enable and disable 
                      // specific devices. 
// First 3 values of the scan array RGB, the last one is the 
// column we lit on each linescan
byte scan[4] = {0x0, 0x0, 0x0, 0x0};

// Each element of data represents a line. Only the first 3 bytes 
// are used one for each RGB color in that same order. A 0 means 
// that color led is on to make computations a little faster (The 
// matrix is common anode so the color bits must be set to LOW in 
// the corresponding register, while the anode is HIGH to lit that 
// LED on)
// We set everything off at the beginning putting a one on each bit

uint32_t data[8] = {
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF, 
  0xFFFFFFFF, 
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF
};
// will use lineScan to render each lien of the data matrix
uint32_t linescan = 0x0;

// The following are the times each color will remain lit for 
// each matrix line scan. 
// We will use it as color correction as with the current 
// algorithm we can't lit a pixel indepently. 
// It can also be used to animate colors globally on each line 
// or the whole matrix. 
long r_time = 100;
long g_time = 70;
long b_time = 60;

int inc = 5;


// r, g and b values will be probably passed as bits but bools use less memory
// and casting time is not crucial in this part of the program, at the  moment I guess 
void setPixel(byte col, byte row, bool r, bool g, bool b) {
  //Setting and clearing a bit require different bit operations so ...
  if (!r) {
    data[row] |= (uint32_t) 1 << (16 + col) ; 
  } else {
    data[row] &= ~((uint32_t) 1 << (16 + col));
  }
  if (!g) {
    data[row] |= (uint32_t) 1 << (8 + col) ; 
  } else {
    data[row] &= ~((uint32_t) 1 << (8 + col));
  }
  if (!b) {
    data[row] |= (uint32_t) 1 << col ; 
  } else {
    data[row] &= ~((uint32_t) 1 << col);
  }
}


//  Renders the contents of the data[] array into the matrix, elements are mapped to rows,
//  each bit (of the first 24) uint32_t array element is mapped to a color color column.
// The order of the bytes es RBG instead of RGB because of the hardware used.
void render(){
  int j;
  for ( j = 0; j < 8; j++) {
    linescan = data[j];
    scan[0] = (byte) (linescan >> 16);
    scan[1] = (byte) linescan;
    scan[2] = (byte) (linescan >> 8);
    scan[3] = 0x01 << j ;
    
    digitalWrite(SS, LOW);
    SPI.transfer(scan[0]);
    SPI.transfer(255);
    SPI.transfer(255);
    SPI.transfer(scan[3]);
    digitalWrite(SS, HIGH);
    delayMicroseconds(r_time);
    
    digitalWrite(SS, LOW);
    SPI.transfer(255);
    SPI.transfer(scan[1]);
    SPI.transfer(255);
    SPI.transfer(scan[3]);
    digitalWrite(SS, HIGH);
    delayMicroseconds(b_time);
    
    digitalWrite(SS, LOW);
    SPI.transfer(255);
    SPI.transfer(255);
    SPI.transfer(scan[2]);
    SPI.transfer(scan[3]);
    digitalWrite(SS, HIGH);
    
    delayMicroseconds(g_time);
  }
}



void setup() {
  Serial.begin(9600);
  
  pinMode(SS, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(15000000, LSBFIRST, SPI_MODE1));
  // put your setup code here, to run once:
  setPixel(0, 0, 1, 1, 1);
  setPixel(1, 0, 0, 1, 1);
  setPixel(2, 0, 0, 0, 1);
  setPixel(3, 0, 1, 1, 0);
  setPixel(4, 0, 1, 0, 1);
  setPixel(5, 0, 1, 0, 0);
  setPixel(6, 0, 0, 1, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  render();
    r_time += inc;
    g_time += inc;
    b_time += inc;
  if (r_time > 300 || b_time > 300 || g_time > 300) {
    inc = -5;
  } else if (r_time <= 0 || g_time <= 0 || b_time <= 0) {
    inc = 5;
  }
  delay(10);
}
*/