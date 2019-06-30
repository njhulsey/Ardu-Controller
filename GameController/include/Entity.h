#include "Main.h"
#include <string.h>

class Entity
{
  public:
      uint16_t x;
      uint16_t y;
      uint16_t size;
      uint16_t x_origin;
      uint16_t y_origin;

  Entity(uint16_t para_x, uint16_t para_y, uint16_t para_size){
      x_origin = x = para_x;
      y_origin = y = para_y;
      size = para_size;
  }

  void tick();
  void render(Adafruit_SSD1305 display);


//display.fillRect();
//display.drawLine
// display.fillRoundRect
//display.drawRoundRect
//testfilltriangle     display.setTextWrap(false);
//testdrawtriangle     display.setCursor(0,0);
//  display.drawCircle  display.setTextSize(1);
//display.write(i);   display.setTextWrap(false);
//display.display(); display.setTextColor(WHITE);
//display.drawBitmap()

//display.drawBitmap(XPos, YPos,  BitMap[], w, h, BLACK/WHITE);
//the bitmap is made up of binary 1,0s
//unsigned char PROGMEM logo16_glcd_bmp[] = {B00000000, B11000000}



};
