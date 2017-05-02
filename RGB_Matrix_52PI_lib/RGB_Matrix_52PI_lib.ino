#include "RGB_Matrix_52PI.h"


RGBMatrix matrix(10);
long counter;
void setup(){
    matrix.setPixel(0, 0, 1, 1, 1);
    matrix.setPixel(1, 0, 0, 1, 1);
    matrix.setPixel(2, 0, 0, 0, 1);
    matrix.setPixel(3, 0, 1, 1, 0);
    matrix.setPixel(4, 0, 1, 0, 1);
    matrix.setPixel(5, 0, 1, 0, 0);
    matrix.setPixel(6, 0, 0, 1, 0);
}

void loop(){
    matrix.render();
    if(counter == 10000) {
      matrix.clear();
      counter = 0;
    }
    counter++;
}
