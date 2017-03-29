#include <Adafruit_NeoPixel.h>

#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#define PIN      6
#define N_ROWS   6
#define N_COLUMNS 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_ROWS * N_COLUMNS, PIN, NEO_GRBW + NEO_KHZ800);

// Colors to be used
uint32_t c0 = strip.Color(0, 0, 0);
uint32_t c1 = strip.Color(10, 30, 0);
uint32_t c2 = strip.Color(40, 10, 0);

uint32_t *ledColors[6][12] = {  
  {&c1, &c1, &c0, &c0, &c0, &c0, &c2, &c2, &c0, &c0, &c0, &c0},
  {&c0, &c0, &c1, &c0, &c0, &c2, &c0, &c0, &c2, &c0, &c0, &c1},
  {&c0, &c0, &c0, &c1, &c2, &c0, &c0, &c0, &c0, &c2, &c1, &c0},
  {&c0, &c0, &c0, &c2, &c1, &c0, &c0, &c0, &c0, &c1, &c2, &c0},
  {&c0, &c0, &c2, &c0, &c0, &c1, &c0, &c0, &c1, &c0, &c0, &c2},
  {&c2, &c2, &c0, &c0, &c0, &c0, &c1, &c1, &c0, &c0, &c0, &c0}
};
uint32_t *pixels[N_ROWS][N_COLUMNS];
int startCol = 0;
int seq = 12;

void setup() {
  strip.begin();
  Serial.begin(9600);
  Serial.println("\n\n\n");
}

void loop() {
  
  for (int r = 0; r < N_ROWS; r++) {
    for (int c = 0; c <  N_COLUMNS ; c++) {
       pixels[r][c] = ledColors[r][(startCol + c)%seq];
       //Serial.println(((c+1)%seq) );
    }
  }
  render();
  delay(90);
  startCol++;

  c1 = strip.Color((40 + (int)(30*sin((startCol*20 - 45)*PI/180)))/5, 30/5, 0);
  c2 = strip.Color(40/5, (30 + (int)(30*sin((startCol*18 + 135)*PI/180)))/5, (5 + (int)(5*sin((startCol*21 + 135)*PI/180)))/5);
}

void render() {
  for (int r = 0; r < N_ROWS; r++) {
    for (int c = 0; c < N_COLUMNS; c++) {
       strip.setPixelColor( r * N_ROWS + c , *pixels[r][c] );
    }
  }
  strip.show();
}

