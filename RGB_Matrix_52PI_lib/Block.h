
#ifndef Block_h
#define Block_h
#include "Arduino.h"
class Block {
    public:
        Block(byte colorBits);
        void rotate();
        void move(byte moveBits);
        update();

    private:
        byte _row;
        byte _col;
        byte _pixels[4]; //Only the first 4 bits of each element contain info
        byte _color; //Only the first 4 bits of each element contain info
        bool alive;
}

#endif