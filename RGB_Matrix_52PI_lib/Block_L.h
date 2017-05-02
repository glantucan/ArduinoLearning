#ifndef Block_L_h
#define Block_L_h
#include "Arduino.h"
#include "Block.h"

class Block_L : public Block{
    public:
        Block_L(byte colorBits);
        
    private:
        byte _states[4][4]; // rotation states
}

#endif