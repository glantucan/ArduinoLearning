
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
        // Each element of _screen represents a line. Only the first 3 bytes 
        // are used one for each RGB color in that same order. A 0 means 
        // that color led is on to make computations a little faster (The 
        // matrix is common anode so the color bits must be set to LOW in 
        // the corresponding register, while the anode is HIGH to lit that 
        // LED on)
        // We set everything off at the beginning putting a one on each bit
        // We only need 24bits for this but there is no uint24_t type, so ...
        uint32_t _screen[8];
        
        /* The following are the times each color will remain lit for 
        each matrix line scan. 
        We will use it as color correction as with the current 
        algorithm we can't lit a pixel indepently. 
        It can also be used to animate colors globally on each line 
        or the whole matrix. I used uint16 to have some margin in case we 
        want delays of the miliseconds order*/
        uint16_t _r;
        uint16_t _g;
        uint16_t _b;
        static const uint32_t _blankScreen[];
};

#endif