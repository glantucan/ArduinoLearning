/*

*/

#include "Arduino.h"
#include "RGB_Matrix_52PI.h"
#include "SPI.h"


const uint32_t RGBMatrix::_blankScreen[8] = {
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};




RGBMatrix::RGBMatrix(byte SS){    
    // Lets initialize the color correction times to a sensible default
    _r = 100;
    _g = 70;
    _b = 60;
    _SS = SS;
    pinMode(SS, OUTPUT);
    clear();
    SPI.begin();
    SPI.beginTransaction(SPISettings(15000000, LSBFIRST, SPI_MODE1));
}

void RGBMatrix::render() {
    int j;
    int col;
    // We'll use a pointer to refeerence the current row of the _screen. This is actually not
    // necessary and it uses a little more memory, so maybe if memory is a concern we should use 
    // array notation directly.
    uint32_t *rowData;
    for ( j = 0; j < 8; j++) {
        rowData = &_screen[j];
        col = 0x01 << j ;
        digitalWrite(SS, LOW);
        SPI.transfer((byte) (*rowData >> 16));
        SPI.transfer(255);
        SPI.transfer(255);
        SPI.transfer(col);
        digitalWrite(SS, HIGH);
        delayMicroseconds(_r);
        
        digitalWrite(SS, LOW);
        SPI.transfer(255);
        SPI.transfer((byte) *rowData);
        SPI.transfer(255);
        SPI.transfer(col);
        digitalWrite(SS, HIGH);
        delayMicroseconds(_b);
        
        digitalWrite(SS, LOW);
        SPI.transfer(255);
        SPI.transfer(255);
        SPI.transfer((byte) (*rowData >> 8));
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
