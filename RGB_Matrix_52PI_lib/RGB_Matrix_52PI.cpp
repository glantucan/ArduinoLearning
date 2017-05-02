/*

*/

#include "Arduino.h"
#include "RGB_Matrix_52PI.h"
#include "SPI.h"

// Each element of _screen represents a line. Only the first 3 bytes 
// are used one for each RGB color in that same order. A 0 means 
// that color led is on to make computations a little faster (The 
// matrix is common anode so the color bits must be set to LOW in 
// the corresponding register, while the anode is HIGH to lit that 
// LED on)
// We set everything off at the beginning putting a one on each bit
const uint32_t _blankScreen[] = {
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF, 
  0xFFFFFFFF, 
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF,
  0xFFFFFFFF
};

/* The following are the times each color will remain lit for 
each matrix line scan. 
We will use it as color correction as with the current 
algorithm we can't lit a pixel indepently. 
It can also be used to animate colors globally on each line 
or the whole matrix. */
uint16_t _r = 100;
uint16_t _g = 70;
uint16_t _b = 60;
RGBMatrix::RGBMatrix(byte SS){
    _SS = SS;
    pinMode(SS, OUTPUT);
    clear();
    SPI.begin();
    SPI.beginTransaction(SPISettings(15000000, LSBFIRST, SPI_MODE1));
}

void RGBMatrix::render() {
    int j;
    int col;
    uint32_t rowData;
    for ( j = 0; j < 8; j++) {
        rowData = _screen[j];
        col = 0x01 << j ;
        digitalWrite(SS, LOW);
        SPI.transfer((byte) (rowData >> 16));
        SPI.transfer(255);
        SPI.transfer(255);
        SPI.transfer(col);
        digitalWrite(SS, HIGH);
        delayMicroseconds(_r);
        
        digitalWrite(SS, LOW);
        SPI.transfer(255);
        SPI.transfer((byte) rowData);
        SPI.transfer(255);
        SPI.transfer(col);
        digitalWrite(SS, HIGH);
        delayMicroseconds(_b);
        
        digitalWrite(SS, LOW);
        SPI.transfer(255);
        SPI.transfer(255);
        SPI.transfer((byte) (rowData >> 8));
        SPI.transfer(col);
        digitalWrite(SS, HIGH);
        delayMicroseconds(_g);
    }
}

void RGBMatrix::colorCorrection(uint16_t r, uint16_t g, uint16_t b) {
    _r = r;
    _g = g;
    _b = b;
}

void RGBMatrix::setPixel(byte col, byte row, bool r, bool g, bool b){
    //Setting and clearing a bit require different bit operations so ...
    if (!r) {
        _screen[row] |= (uint32_t) 1 << (16 + col) ; 
    } else {
        _screen[row] &= ~((uint32_t) 1 << (16 + col));
    }
    if (!g) {
        _screen[row] |= (uint32_t) 1 << (8 + col) ; 
    } else {
        _screen[row] &= ~((uint32_t) 1 << (8 + col));
    }
    if (!b) {
        _screen[row] |= (uint32_t) 1 << col ; 
    } else {
        _screen[row] &= ~((uint32_t) 1 << col);
    }
}
void RGBMatrix::clear() {
    for (byte i = 0; i < 8; i++){
        _screen[i] = _blankScreen[i];
    }
}
