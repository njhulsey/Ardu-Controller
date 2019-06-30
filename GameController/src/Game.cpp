#include "Game.h"
#include "Main.h"
#include "Entity.h"
#include "Snake.h"


// software SPI
//Adafruit_SSD1305 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// hardware SPI is much faster
Adafruit_SSD1305 display(OLED_DC, OLED_RESET, OLED_CS);
Snake player(59,27,10);

boolean shouldDraw = false;
int drawCounter = 0;

void gameStart(){
  display.begin();
  display.display(); // show splashscreen
  delay(500);
  display.clearDisplay();   // clears the screen and buffer

  // Draw the Border
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  display.display();
  delay(500);


}

void tick(){
  //Serial.println("tick!");
  player.erase(display);
  display.display();

  player.tick();




}

void render(){
    //display.clearDisplay();
    //*****BEGIN RENDER******
    //display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    player.render(display);
    //display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);

    //display changes
    display.display();
}
