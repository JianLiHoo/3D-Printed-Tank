#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12); // RX, TX

int joyLy;
int joyRy;
boolean left;
boolean right;

#define leftBtn 5
#define rightBtn 4

void setup() {
  Serial.begin(9600);
  pinMode(leftBtn, INPUT_PULLUP);
  pinMode(rightBtn, INPUT_PULLUP);

  mySerial.begin(38400);
}

void loop() {
  String bluetooth = "";
  left = digitalRead(leftBtn);
  right = digitalRead(rightBtn);
  if (left == LOW){
    bluetooth = bluetooth + '1';
  }
  else{
    bluetooth = bluetooth + '0';
  }
  
  if (right == LOW){
    bluetooth = bluetooth + '1';
  }
  else{
    bluetooth = bluetooth + '0';
  }

  joyLy = analogRead(A2);
  joyRy = 1023 - analogRead(A4); //flip the values
  //joyLy = map(joyLy,0,1023,0,255);  //conversion on tank
  //joyRy = map(joyRy,0,1023,0,255);

  bluetooth = bluetooth + joyLy;
  bluetooth = bluetooth + ',';
  bluetooth = bluetooth + joyRy;
  //bluetooth = bluetooth + 'c';
  mySerial.println(bluetooth);  // \n used for cancel
  delay(10);

}
