#include <Servo.h>

#define rudderServoPin 3
#define elevatorServoPin 5
#define aileronRightPin 9
#define aileronLeftPin 10

#define rudderServoOffset 25
#define elevatorServoOffset 0
#define aileronRightOffset 0
#define aileronLeftOffset 0


Servo rudderServo;
Servo elevatorServo;
Servo aileronRightServo;
Servo aileronLeftServo;
/*
 * servo down = 90, horizontal
 * servo left = 0, going up
 * servo right = 180, going down
 */

int rudderServoPos=0,
  elevatorServoPos=0,
  aileronRightServoPos=0,
  aileronLeftServoPos=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  rudderServo.attach(rudderServoPin);
  elevatorServo.attach(elevatorServoPin);
  aileronRightServo.attach(aileronRightPin);
  aileronLeftServo.attach(aileronLeftPin);
  test();
//  rudderServoWrite(0);
//  elevatorServoWrite(0);
//  aileronRightWrite(180);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void rudderServoWrite(int degreeChange){
  if(degreeChange>=0 && degreeChange<=180){
    rudderServo.write(rudderServoPos+rudderServoOffset+degreeChange);
  }
}
void elevatorServoWrite(int degreeChange){
  //if(degreeChange>=0 && degreeChange<=180){
    elevatorServoPos = elevatorServoPos+elevatorServoOffset+degreeChange;
    elevatorServo.write(elevatorServoPos);
  //}
}

void aileronRightWrite(int degreeChange){
  //if(degreeChange>=0 && degreeChange<=180);
    aileronRightServoPos = aileronRightServoPos+elevatorServoOffset+degreeChange;
    aileronRightServo.write(aileronRightServoPos);
  //}
}

void test(){
  rudderServo.write(90);
  elevatorServo.write(90);
  aileronRightServo.write(90);
  aileronLeftServo.write(90);
  delay(500);
}


