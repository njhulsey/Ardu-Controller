#include "Main.h"
#include "Body.h"

class Snake : public Entity {

  public:
    uint8_t speed;
    uint8_t counter;
    char direction;
    uint8_t body_size = 55;
    uint8_t score = 0;
    struct Body bodies[55];
    boolean gameOver;
    uint8_t state;

    Snake(uint16_t para_x, uint16_t para_y, uint16_t para_size)
    : Entity(para_x,para_y,para_size){
      counter = 0;
      direction = 'r';
      score =0;
      speed = 5;
      gameOver = false;

      for (uint8_t i = 0; i < body_size; i++) {
        bodies[i].isAlive = false;
        bodies[i].state = 0;
      }

    }

    void tick(){
      counter ++;
      if(counter >= (speed - (score/body_size))){
        counter = 0;

        for(uint8_t i = 0; i < body_size; i++){
           if(bodies[i].isAlive == false){
              bodies[i].x = x;
              bodies[i].y = y;
              bodies[i].isAlive = true;
              bodies[i].state = 1;
              bodies[i].life = millis() + ((speed + score) * 100);
              break;
            }
        }

        switch(direction){
          case 'u': moveUp();
            break;
          case 'd': moveDown();
            break;
          case 'l': moveLeft();
            break;
          case 'r': moveRight();
            break;
          default:
            break;
        }


        for (uint8_t i = 0; i < body_size; i++){

          if(bodies[i].x == x && bodies[i].isAlive && bodies[i].y == y){
              gameOver = true;
          }

          if(bodies[i].isAlive && bodies[i].life < millis()){
              bodies[i].isAlive = false;
              bodies[i].state = 2;
              //bodies[i].x = -10;
              //bodies[i].y = -10;
          }
        }


      }
      //tick body
      //check if body is dead if so then delete

      if(digitalRead(UP_BUTTON) == HIGH && direction != 'd')
        direction = 'u';
      if(digitalRead(DOWN_BUTTON) == HIGH && direction != 'u')
        direction = 'd';
      if(digitalRead(LEFT_BUTTON) == HIGH && direction != 'r')
        direction = 'l';
      if(digitalRead(RIGHT_BUTTON) == HIGH && direction != 'l')
        direction = 'r';

        if(analogRead(Y_JOYSTICK) > 900 && score < (body_size - 1) * speed)
          score += 1;


    }

    void resetGame(Adafruit_SSD1305 display){
      gameOver = false;

      score = 0;
      direction = 'r';
      speed = 5;


      display.fillRect(x + 1,y + 1,size - 1,size - 1,BLACK);
      x = x_origin;
      y = y_origin;

      for(uint8_t i = 0 ; i < body_size; i++){
        display.fillRect(bodies[i].x + 1,bodies[i].y + 1,
         size - 1, size - 1,BLACK);
          bodies[i].isAlive = false;
      }
      
      display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    }

    void erase(Adafruit_SSD1305 display){
      if(gameOver){
        resetGame(display);
      }
      //erase
      if(counter == 0)
        display.fillRect(x + 1,y + 1,size - 1,size - 1,BLACK);

      for (uint8_t i = 0; i < body_size; i++){
        if(bodies[i].state == 2){
        //  display.fillRect(bodies[i].x + 1,bodies[i].y + 1,
        //   size - 1, size - 1,BLACK);
           bodies[i].state = 0;
           display.fillRect(bodies[i].x + 1,bodies[i].y + 1,
            size - 1, size - 1,BLACK);
          }
        }


    }

    void render(Adafruit_SSD1305 display){
        //display.drawRect(x,y,size,size,WHITE);
        /*display.drawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
          64 + 64 * cos((PI/12)* counter),
          32 + 32 * sin((PI/12) * counter),
          WHITE);*/
          //Serial.print(to_String((cos(PI/12) * counter)));
          //display.drawBitmap(x, y,  animal, 16, 16, WHITE);

          //render body
        //  display.fillRect(x + 1,y + 1,size - 1,size - 1,BLACK);
        //draw player
        if(counter < 2)
          display.fillRect(x + 1,y + 1,size - 1,size - 1,WHITE);

          //draw body
          for (uint8_t i = 0; i < body_size; i++){
            if(bodies[i].state == 1){
            //  display.fillRect(bodies[i].x + 1,bodies[i].y + 1,
            //   size - 1, size - 1,BLACK);
               bodies[i].state = 0;
               display.fillRect(bodies[i].x + 1,bodies[i].y + 1,
                size - 1, size - 1,WHITE);
              }
            }

    }

    void moveUp(){
      y -= size;
    }
    void moveDown(){
      y += size;
    }
    void moveLeft(){
      x -= size;
    }
    void moveRight(){
      x += size;
    }

};
