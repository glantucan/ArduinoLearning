#ifndef Floor_h
#define Floor_h

#include "Arduino.h"
#include "Block.h"

class Floor {
    public:
        Floor(byte width);
        void addBlock(const Block &block);
        void update();
    private:

};

#endif