
#ifndef RGBMatrix_h
#define RGBMatrix_h

#include "Arduino.h"

class RGBMatrix {
    public:
        RGBMatrix(byte SS);
        void render();
        void colorCorrection(uint16_t r, uint16_t g, uint16_t b);
        void setPixel(byte x, byte y, bool r, bool g, bool b);
        void clear();
    private:
        byte _SS;
        uint32_t _screen[8];
        uint32_t _rowData;
        uint16_t _r;
        uint16_t _g;
        uint16_t _b;
};

#endif