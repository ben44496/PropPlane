
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

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
const int RUDDER_PIN = 3;
const int ELEVATOR_PIN = 5;
const int AILERONR_PIN = 9;
const int AILERONL_PIN = 10; 
#endif

const int RUDDER_START = 100;
const int RUDDER_END = 550;
const int ELEVATOR_START = 240;
const int ELEVATOR_END = 600;
const int AILERONL_START = 120; 
const int AILERONL_END = 550; 
const int AILERONR_START = 125; 
const int AILERONR_END = 560; 


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start");

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



void loop() {

//for(int i=0; i<180; i++){
//  roll(i);
//  pitch(i);
//  yaw(i);
//}
//roll(0); //<=--- left
//delay(400);
//roll(180); //<=--- right
//delay(400);
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
void pitch(int degree){
  if(degree>=0 && degree<=180){
  setServo(1, degree);
  }
}
/**
 * 180 to the right, 0 to the left
 */
void roll(int degree){
  /*if(degree==90){
    setServo(2, 90);
    setServo(3, 90);
  }else{
    setServo(3,degree);
    setServo(2,degree);
  }
*/
  if(degree>=0 && degree<=180){
  setServo(2, degree);
  setServo(3, degree);
  }
}
void yaw(int degree){
  if(degree>=0 && degree<=180){
  setServo(0, degree);
  }
}






void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

