#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12); // RX, TX

int pos = 0; // button pos
String bluetooth; //val from bluetooth
char leftButton;
char rightButton;

//Motor A

int in1 = 5;
int in2 = 6;

int motorAVal;

//Motor B

int in3 = 9;
int in4 = 10;

int motorBVal;

void setup() {
  Serial.begin(38400);
  /*
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  */
  mySerial.begin(38400);
}
/*
void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
*/

void loop() {
  if (mySerial.available()){
    bluetooth = mySerial.readStringUntil('\n');

    //Parsing

    leftButton = bluetooth.charAt(0);
    rightButton = bluetooth.charAt(1);
    bluetooth.remove(0,2);
    //Serial.println(bluetooth);
    motorAVal=bluetooth.substring(0,bluetooth.indexOf(',')).toInt();
    motorBVal=bluetooth.substring(bluetooth.indexOf(',')+1).toInt();
    
    //Serial.println(motorBVal);
    motorAVal=map(motorAVal,0,1023,-255,255);
    motorBVal=map(motorBVal,0,1023,-255,255);

    

    //--------Direction-----------
    if((motorAVal<-10)&&(motorBVal<-10)){ //A Rev, B Rev
      analogWrite(in1,0);
      analogWrite(in2,abs(motorAVal));

      analogWrite(in3,0);
      analogWrite(in4,abs(motorBVal));
    }
    else if((motorAVal>10)&&(motorBVal>10)){  //A Fwd, B Fwd
      analogWrite(in1,abs(motorAVal));
      analogWrite(in2,0);

      analogWrite(in3,abs(motorBVal));
      analogWrite(in4,0);
    }
    else if((motorAVal>10)&&(motorBVal<-10)){  //A Fwd, B Rev
      analogWrite(in1,abs(motorAVal));
      analogWrite(in2,0);

      analogWrite(in3,0);
      analogWrite(in4,abs(motorBVal));
    }
    else if((motorAVal<-10)&&(motorBVal>10)){  //A Rev, B Fwd
      analogWrite(in1,0);
      analogWrite(in2,abs(motorAVal));
      
      analogWrite(in3,abs(motorBVal));
      analogWrite(in4,0);
    }
    else if((motorAVal<-10)&&((motorBVal>-10)&&(motorBVal<10))){  //A Rev, B Stop
      analogWrite(in1,0);
      analogWrite(in2,abs(motorAVal));
      
      analogWrite(in3,0);
      analogWrite(in4,0);
    }
    else if((motorAVal>10)&&((motorBVal>-10)&&(motorBVal<10))){  //A Fwd, B Stop
      analogWrite(in1,abs(motorAVal));
      analogWrite(in2,0);
      
      analogWrite(in3,0);
      analogWrite(in4,0);
    }
    else if((motorBVal<-10)&&((motorAVal>-10)&&(motorAVal<10))){  //A Stop, B Rev
      analogWrite(in1,0);
      analogWrite(in2,0);
      
      analogWrite(in3,0);
      analogWrite(in4,abs(motorBVal));
    }
    else if((motorBVal>10)&&((motorAVal>-10)&&(motorAVal<10))){  //A Stop, B Fwd
      analogWrite(in1,0);
      analogWrite(in2,0);
      
      analogWrite(in3,abs(motorBVal));
      analogWrite(in4,0);
    }
    
    else{ //All stop
      analogWrite(in1,0);
      analogWrite(in2,0);
      
      analogWrite(in3,0);
      analogWrite(in4,0);
    }

    
    Serial.print(motorAVal);
    Serial.println(motorBVal);

  }
}

