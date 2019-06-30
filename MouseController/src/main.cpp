#include "Main.h"


Adafruit_SSD1305 display(OLED_DC, OLED_RESET, OLED_CS);

void setup() {
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

  display.begin();


  display.display();
  delay(200);
  display.clearDisplay();

  refreshScreen();


  Serial.begin(128000); //9600 19200 115200
  Serial.print("Start Setup:");
}

int pause = 30;
int steps = 50;

int left_last = LOW;
int right_last = LOW;
int down_last = LOW;

int up_button_last = LOW;

String data[8];

String pressW = "";
String pressA = "";
String pressS = "";
String pressD = "";

void loop() {

  int move_tolerance = 350;

  int slow_speed = 4;
  int readY = analogRead(Y_JOYSTICK) - 500;
  int readX = analogRead(X_JOYSTICK) - 500;

  int moveX = (int)((steps/500.0) * readX);
  int moveY = (int)((steps/500.0) * readY);

  //facing left
  if( readX > -1 * move_tolerance && readX < -10){
    moveX = -slow_speed;
  }

  if(readX < move_tolerance && readX > 10){
    moveX = slow_speed;
  }

  if(readY < move_tolerance && readY > 10){
    moveY = slow_speed;
  }

  if(readY > -1 * move_tolerance && readY < -10){
    moveY = -slow_speed;
  }

  if(digitalRead(DOWN_BUTTON) == HIGH){
      //facing left
      if( readX < 0 ){
        moveX = -slow_speed;
      }

      if(readX > 0){
        moveX = slow_speed;
      }

      if(readY > 0){
        moveY = slow_speed;
      }

      if(readY < 0 ){
        moveY = -slow_speed;
      }
  }

  if((readX >= -10 && readX < 0)|| (readX <= 10 && readX > 0))
    moveX = 0;

  if((readY >= -10 && readY < 0) || (readY <= 10 && readY > 0))
    moveY = 0;

  if(digitalRead(UP_BUTTON) == LOW ){
      Serial.print("M:"+String(moveX) + ":" +String(moveY) + ":");
      delay(pause);
  }


  String press = "";
  if(digitalRead(UP_BUTTON) != up_button_last){
    if(digitalRead(UP_BUTTON) == LOW)
      Serial.print("K:W:U:A:U:S:U:D:U:");

    delay(pause);
    up_button_last = digitalRead(UP_BUTTON);
  }


  if(digitalRead(UP_BUTTON) == HIGH){
    int tolerance = 100;
    pressW = "U"; pressS = "U";
    pressA = "U"; pressD = "U";

    if(readX > tolerance) {pressA = "D"; pressD = "U";}
    if(readX < -1 * tolerance) {pressD = "D"; pressA = "U";}
    if(readY > tolerance) {pressW = "U"; pressS = "D";}
    if(readY < -1 * tolerance) {pressS = "U"; pressW = "D";}


    Serial.print("K:W:" + pressW + ":A:" + pressA + ":S:" + pressS + ":D:" + pressD + ":");
    delay(pause);
  }

  //Left click
  if (digitalRead(RIGHT_BUTTON) == HIGH && right_last == LOW) {
    Serial.print("B:R:");
    delay(pause);
  }
  right_last = digitalRead(RIGHT_BUTTON);


  //Right Click
  if (digitalRead(LEFT_BUTTON) == HIGH && left_last == LOW) {
    Serial.print("B:L:");
    delay(pause);
  }
  left_last = digitalRead(LEFT_BUTTON);




  if(Serial.available() > 0){
    String raw = Serial.readStringUntil(':');
    int index = raw.charAt(0) - '0';
    String text = raw.substring(1);
    data[index] = text;
    refreshScreen();
  }

  if(digitalRead(DOWN_BUTTON) == HIGH && down_last == LOW){
    Serial.print("B:D:");
    delay(pause);
  }
  down_last = digitalRead(DOWN_BUTTON);




}

void refreshScreen(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  display.println(data[0]);
  display.println("Hitpoints:" + data[1]);
  display.println("Attack:" + data[2]);
  display.println("Strength:" + data[3]);
  display.println("Defence:" + data[4]);
  display.println("Ranged:" + data[5]);
  display.println("Magic:" + data[6]);
  display.display();
}
