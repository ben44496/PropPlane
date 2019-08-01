#include <NeoSWSerial.h>
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin_L = 0; // analog pin connected to X output
const int Y_pin_L = 2; // analog pin connected to Y output
const int X_pin_R = 1; // analog pin connected to X output
const int Y_pin_R = 3; // analog pin connected to Y output
const int T_pin_L = 4; // analog pin connected to sliding potentiometer
const int T_pin_R = 5; // analog pin connected to sliding potentiometer
NeoSWSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
void setup() {
  HC12.begin(9600);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
 
}

void loop() {
  //down left is 10
  // up right is 0
  int XL = analogRead(X_pin_L);
  int YL = analogRead(Y_pin_L);
  int XR = analogRead(X_pin_R);
  int YR = analogRead(Y_pin_R);
  int TL = analogRead(T_pin_L);
  int TR = analogRead(T_pin_R);
//  Serial.print(XL);
//  //Serial.print(" ");
//  Serial.print(XR);
// // Serial.print(" ");
//  Serial.print(YL);
//  //Serial.print(" ");
//  Serial.print(YR);
//  Serial.println(" ");
//  Serial.print(analogRead(4));
//  
//  Serial.println(analogRead(5));
Serial.print("Q");
  Serial.print(XL);
  Serial.print("W");
  Serial.print(YL);
  Serial.print("E");
  Serial.print(XR);
  Serial.print("R");
  Serial.print(YR);
  Serial.print("D");
  Serial.print(TL);
  Serial.print("F");
  Serial.print(TR);
  Serial.println();
//  if(XR == 10) XR = 9;
//  if(XL == 10) XL = 9;
//  if(YL == 10) YL = 9;
//  if(YR == 10) YR = 9;
 // uint32_t format = XL*1000000+YL*10000+XR*100+YR;
  HC12.print("Q");
  HC12.print(XL);
  HC12.print("W");
  HC12.print(YL);
  HC12.print("E");
  HC12.print(XR);
  HC12.print("R");
  HC12.print(YR);
  HC12.print("D");
  HC12.print(TL);
  HC12.print("F");
  HC12.print(TR);
  HC12.println();
  delay(100);
}
