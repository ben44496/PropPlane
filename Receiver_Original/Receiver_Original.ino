#include  <Servo.h>
#include <NeoSWSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
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
void loop() {
  

  ///////////////////
  
  String in = "";
  
  while (HC12.available()) {        // If HC-12 has data
    String potentiometer = "";
    char input = HC12.read();// Send the data to Serial monitor
    //Serial.print(input);
    if(input == 'Q'){
      pos=0;
      //Serial.print("Q");
    }else if(input == 'W'){
      pos=1;
      //Serial.print("W");
    }else if(input == 'E'){
      pos=2;
      //Serial.print("E");
    }else if(input == 'R'){
      pos=3;
      //Serial.print("R");
    }else if(input == '\n'){
      //Serial.println();
    }else if(isDigit(input)){
      if(pos >=0 && pos <=4){
      movement[pos] = input - '0';
      //Serial.print(movement[pos]);
      }else if(pos ==4 || pos ==5){
        potentiometer += input;
      }
    }else if(input == 'D'){
      pos=4;
      potentiometer = "";
    }else if(input == 'F'){
      pos=5;
      potentiometer = "";
    }
//    if (input == '\n') break;
//    in += input;
    
    
    
  }
  
//    if(in.length() >0) Serial.println(in);
//    int pos =0;


    //ESC.write((10-movement[1])/10.0*2000);
   //throttle

    Serial.print(movement[0]);
    Serial.print(movement[1]);
    Serial.print(movement[2]);
    Serial.print(movement[3]);
    Serial.print(movement[4]);
    Serial.println(movement[5]);

    
    
    //Serial.println((10-movement[1]));
    //Serial.println((10 -movement[1])/10.0*2000);
    
}
