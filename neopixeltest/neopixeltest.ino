// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN      6
#define N_LEDS   36

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRBW);

void setup() {
  strip.begin();
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    //strip.setPixelColor(8  , strip.Color(0, 0, 0, 100));
    //strip.setPixelColor(14  , strip.Color(65, 100, 40)); // (.65, 1, .4)
//     strip.setPixelColor(14  , strip.Color(255, 0, 0));
//     strip.setPixelColor(15  , strip.Color(0, 255, 0));
//     strip.setPixelColor(20  , strip.Color(0, 0, 255));
//     strip.setPixelColor(21  , strip.Color(100, 100, 100));
     //strip.show();
  }
}

void loop() {
  chase(strip.Color(50, 0, 0)); // Red
  chase(strip.Color(0, 50, 0));
  chase(strip.Color(0, 0, 50));
  chase(strip.Color(0, 0, 0, 50));
  chase(strip.Color(50, 50, 50));
  
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(500);
  }
}
