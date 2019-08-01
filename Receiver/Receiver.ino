#include  <Servo.h>
#include <NeoSWSerial.h>

NeoSWSerial HC12(5, 4); // HC-12 TX Pin, HC-12 RX Pin
Servo ESC;
void setup() {
  ESC.attach(3,1000,2000);
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);// Serial port to HC12
  ESC.write(0);
  delay(1000);
  ESC.write(2000);
  delay(1000);
  ESC.write(0);
  delay(1000);
  //ESC.write(2000);
  //delay(1000);
  //ESC.write(0);
}
int movement[6];
int pos=0;
String number = "";
void loop() {
  

  ///////////////////
  
  String in = "";
  while (HC12.available()) {        // If HC-12 has data
    
    char input = HC12.read();// Send the data to Serial monitor
    //Serial.print(input);
    if(input == 'Q'){
      movement[pos] = number.toInt();
      number = "";
      pos=0;
      //Serial.print("Q");
    }else if(input == 'W'){
      movement[pos] = number.toInt();
      number = "";
      pos=1;
      //Serial.print("W");
    }else if(input == 'E'){
      movement[pos] = number.toInt();
      number = "";
      pos=2;
      //Serial.print("E");
    }else if(input == 'R'){
      movement[pos] = number.toInt();
      number = "";
      pos=3;
      //Serial.print("R");
    }else if(input == 'D'){
      movement[pos] = number.toInt();
      number = "";
      pos=4;
    }else if(input == 'F'){
      movement[pos] = number.toInt();
      number = "";
      pos=5;
    }else if(isDigit(input)){
      if(number.length()<4);
      number += input;
    }
    
    
    
  }
  
//    if(in.length() >0) Serial.println(in);
//    int pos =0;


    //ESC.write((10-movement[1])/10.0*2000);
   //throttle

    Serial.print(movement[0]);
    Serial.print(" ");
    Serial.print(movement[1]);
    Serial.print(" ");
    Serial.print(movement[2]);
    Serial.print(" ");
    Serial.print(movement[3]);
    Serial.print(" ");
    Serial.print(movement[4]);
    Serial.print(" ");
    Serial.println(movement[5]);
    

    
    
    //Serial.println((10-movement[1]));
    //Serial.println((10 -movement[1])/10.0*2000);
    
}
