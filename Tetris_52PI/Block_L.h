#ifndef Block_L_h
#define Block_L_h

#include "Arduino.h"
#include "Block.h"

class Block_L : public Block{
    public:
        Block_L(byte colorBits);
        
    private:
        // rotation states
        static const byte state_0;
        static const byte state_1;
        static const byte state_2;
        static const byte state_3;
};

#endif