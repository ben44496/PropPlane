#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include  <Servo.h>
//#include <SoftwareSerial.h>
#include <NeoSWSerial.h>


#define rudderPin 0
#define elevatorPin 1
#define aileronLPin 2
#define aileronRPin 3


#if defined(ESP8266)
const int RUDDER_PIN = 14; // D5
const int ELEVATOR_PIN = 12; // D6
const int AILERONR_PIN = 13; // D7
const int AILERONL_PIN = 0; // D7  //<-- change this pin to match the right one.
#elif defined(ESP32)
const int RUDDER_PIN = 5;
const int ELEVATOR_PIN = 18;
const int AILERONR_PIN = 19;
const int AILERONL_PIN = 0; //<-- change this pin to match the right one.
#else
const int THROTTLE_PIN = 3;
#endif


const int RUDDER_START = 200;//220
const int RUDDER_END = 430;//430
const int ELEVATOR_START = 300;
const int ELEVATOR_END = 540;
const int AILERONL_START = 120; 
const int AILERONL_END = 550; 
const int AILERONR_START = 125; 
const int AILERONR_END = 560;

const int CONTROLLER_CONSTANT = 9;
const int MOTOR_START = 1000; 
const int MOTOR_END = 1200; 

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

  const byte HC12RxdPin = 4;                  // Recieve Pin on HC12
const byte HC12TxdPin = 5;                  // Transmit Pin on HC12

NeoSWSerial HC12(HC12TxdPin,HC12RxdPin); // HC-12 TX Pin, HC-12 RX Pin
Servo ESC;

int movement[4];
int throttleVelocity = -1; //from 0-180

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  ESC.attach(THROTTLE_PIN);
  //ESC.attach(THROTTLE_PIN,MOTOR_START,MOTOR_END);
  HC12.begin(9600);// Serial port to HC12
  Serial.println("motor ready");
  delay(5000);
  ESC.write(0);
  delay(1000);
  ESC.write(2000);
  delay(1000);
  ESC.write(0);
  delay(1000);
  ESC.write(0);

  pwm.begin();
  pwm.setPWMFreq(60); //max pwm frequency

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  /*
   * Accepted values are 100000 (standard mode) and 400000 (fast mode). 
   * Some processors also support 10000 (low speed mode), 1000000 (fast mode plus) and 3400000 (high speed mode). 
   * Please refer to the specific processor documentation to make sure the desired mode is supported.
   */
  //Wire.setClock(100000);
  
  
  delay(500);
  yield();
  testing();
  
}
int pos=0;
void loop() {
  // put your main code here, to run repeatedly:




//////////////
//motor code/////////////////////////////////////////////////////////////////
//////////////
//String in = "";

  
  while (HC12.available()) {        // If HC-12 has data
    
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
      movement[pos] = input - '0';
      //Serial.print(movement[pos]);
    }
//    if (input == '\n') break;
//    in += input;
    
    
    
  }

    
////////////////////////////////////////////////////////////////////////////

/*
 * roll();
 * pitch();
 * yaw();
 * change throttle Velocity according to joystick
 * throttle(throttleVelocity);
 */



/////////////////////////////////////////////////////////////////////////////

change();


}

















void change(){
  //movement[0] = 5; //<=----- TAKING OUT THE AILERON CUZ THEY INTERFERENCE
  rolll(18*(CONTROLLER_CONSTANT-movement[0]));
  yaww(18*(CONTROLLER_CONSTANT-movement[1]));
  int throttleChange = 18*(CONTROLLER_CONSTANT-movement[2]) - 72;
  int throttleVelocity = 18*(CONTROLLER_CONSTANT-movement[2]);
  
  pitchh(18*(CONTROLLER_CONSTANT-movement[3]));
  
  //throttleAccel(throttleChange);
  throttle(throttleVelocity); //<<=---------- you have to input the change in throttleAccel code to change throttle Velocity when u move the joystick

  Serial.println();
}
/**
 * Changes the pwm value according to throttleVelocity
 */
void throttle(int num){
  int value = 0;
  value = ((num/180.0)*(MOTOR_END-MOTOR_START))+MOTOR_START;
  if(num < 0){
    ESC.write(value);
  }else if (num >= 0 && num <=180){
    
    ESC.write(value);
  }
  Serial.print("T");
  Serial.print(value);
  //Serial.print(throttleVelocity);
  Serial.print(" ");
}

/**
 * Changes throttleVelocity depending on the input of the function. It works by having
 * every loop change the pwm frequency to the throttleVelocity value.
 */
void throttleAccel(int accel){
  //int accel = 
  if(throttleVelocity == -1 && accel > 0){
    throttleVelocity = 0;
    delay(500);
  }
  else if ((throttleVelocity +accel) >180){
    throttleVelocity = 180;
  }
  else if ((throttleVelocity + accel)<0){
    throttleVelocity = -1;
  }else if ((throttleVelocity + accel)>0 && (throttle+accel) <180){
    throttleVelocity +=accel;
  }
  throttle(throttleVelocity);
}

/**
 * Tests once at the start of the program to make sure everything is working.
 */
void testing(){
  Serial.println("Start Test.");
    for(int i=0; i<4; i++){
      setServo(i,0);
      delay(500);
      setServo(i,90);
      delay(500);
      setServo(i,180);
      delay(500);
      setServo(i,90);
      delay(500);
    Serial.println("Testing Pin: " + i);
  }
  Serial.println("Finished Test.");
  delay(1000);
}
/**
 * Takes in two arguments, the pin for the servo, and 0-180 for the degree.
 */
void setServo(int pin, int degree){
  //degree between 0-180
  if(pin == 0){
    pwm.setPWM(rudderPin, 0, calculate(pin,degree)); //100-550, 0-180;
  }else if (pin ==1){
    pwm.setPWM(elevatorPin, 0, calculate(pin,degree)); //290-600, 0,180;
  }else if (pin ==2){
    pwm.setPWM(aileronLPin, 0, calculate(pin,degree));
  }else if (pin ==3){
    pwm.setPWM(aileronRPin, 0, calculate(pin,degree)); //125-342-560, 0-180;
  }
  //Serial.println(""+Pin+ ", "+ degree);
}
int calculate(int pin, int degree){
  int startVal=0, endVal=0;
  if(pin==0){
    startVal = RUDDER_START;
    endVal = RUDDER_END;
  }else if(pin==1){
    startVal = ELEVATOR_START;
    endVal = ELEVATOR_END;
  }else if(pin==2){
    startVal = AILERONL_START;
    endVal = AILERONL_END;
  }else if(pin==3){
    startVal = AILERONR_START;
    endVal = AILERONR_END;
  }
  return (((degree/180.0)*(endVal-startVal))+startVal);
}
/**
 * From zero to 100 percent, 0 to 180;
 */
void pitchh(int degree){
  if(degree>=0 && degree<=180){
  setServo(1, degree);
  }
  Serial.print("P");
  Serial.print(degree);
  Serial.print(" ");
}
/**
 * 180 to the right, 0 to the left
 */
void rolll(int degree){
  if(degree>=0 && degree<=180){
  setServo(2, degree +18); //<---------------------------------------------------------------------------DANGEROUS
  setServo(3, degree);
  }
  Serial.print("R");
  Serial.print(degree);
  Serial.print(" ");
}

void yaww(int degree){
  if(degree>=0 && degree<=180){
  setServo(0, degree+18); //<---------------------------------------------------------------------------DANGEROUS
  }
  Serial.print("Y");
  Serial.print(degree);
  Serial.print(" ");
}

/**
 * Increases the throw for the rudder and elevator
 */
void fullMotionRangeSettings(){
//  RUDDER_START = 100;
//  RUDDER_END = 550;
//  ELEVATOR_START = 240;
//  ELEVATOR_END = 600;
//  AILERONL_START = 120; 
//  AILERONL_END = 550; 
//  AILERONR_START = 125; 
//  AILERONR_END = 560;
}

