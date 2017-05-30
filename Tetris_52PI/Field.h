#ifndef Field_h
#define Field_h

#include "Arduino.h"
#include "Floor.h"

class Field {
    public:
        Field(const Floor &floor, byte height);
        bool checkPixel(byte row, byte column);
    private:

};

#endif