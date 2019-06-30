#include "Main.h"




struct Body{

  uint16_t x;
  uint16_t y;
  unsigned int life;
  uint8_t state;
  boolean isAlive;

};
/*

class Body : public Entity{
  public:
    unsigned long life;
    boolean isAlive;


  Body(uint16_t para_x, uint16_t para_y, uint16_t para_size, uint16_t para_life)
  : Entity(para_x, para_y, para_size){
    life = para_life;
    isAlive = false;
  }

  void tick(){
    if(millis() > life){
      life = 0;
      isAlive = false;
      x = 0;
      y = 0;
    }

  }

  void render(Adafruit_SSD1305 display){
      display.fillRect(x + 1,y + 1,size - 1,size - 1,WHITE);
  }

};
*/
