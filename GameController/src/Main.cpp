#include "Main.h"
#include "Game.h"



unsigned long fps = 0.0L;
unsigned long game_speed = 0.0L;

//Adafruit_SSD1305 display;
void setup()   {
  delay(1500);

  //TODO: MAKE THIS ALL LOW LEVEL C DDRD = 0b10001....
  //ITS MUCH FASTER
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(Y_JOYSTICK,INPUT);
  pinMode(X_JOYSTICK,INPUT);

  pinMode(UP_BUTTON,INPUT);
  pinMode(LEFT_BUTTON,INPUT);
  pinMode(DOWN_BUTTON,INPUT);
  pinMode(RIGHT_BUTTON,INPUT);

  pinMode(BUZZER,OUTPUT);

  digitalWrite(RED_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BLUE_LED, HIGH);   // turn the LED on (HIGH is the voltage level)

  fps = millis() + (100);
  game_speed = millis() + (100);

  gameStart();
}


void loop() {

  //if(millis() > game_speed){
    game_speed = millis() + (15);
    tick();
  //}

  //if(millis() > fps){
    fps = millis() + (120);
    render();
  //}


  //delay(1);
}
