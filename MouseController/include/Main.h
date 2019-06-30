#include "Arduino.h"
#include <String.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>


#define BLUE_LED 14
#define RED_LED 15

#define Y_JOYSTICK A2
#define X_JOYSTICK A3

#define UP_BUTTON 2
#define LEFT_BUTTON 3
#define DOWN_BUTTON 4
#define RIGHT_BUTTON 7

#define BUZZER 5

#define OLED_CLK 13
#define OLED_MOSI 11

// Used for software or hardware SPI
#define OLED_CS 10
#define OLED_DC 8

// Used for I2C or SPI
#define OLED_RESET 9

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

void refreshScreen();
