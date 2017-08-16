#include <Arduino.h>

#ifndef INDICATORLED_H
#define INDICATORLED_H
struct Color{
  float r;
  float g;
  float b;
  Color(){
    r = 0;
    g = 0;
    b = 0;
  }
  Color(float x,float y, float z){
    r = x;
    g = y;
    b = z;
  }
};
const Color red = Color(1.0,0,0);
const Color green = Color(0,1.0,0);
const Color blue = Color(0,0,1.0);
const Color cyan = Color(0,1.0,0.6);
const Color yellow = Color(1.0,1.0,0);
const Color orange = Color(1.0,0.4,0);

class IndicatorLED{
private: 
  Color color;
  const int ledSwitch = 2;
  const int redPin = 11;
  const int greenPin = 10;
  const int bluePin = 9;
  const int PWMStep = 255;
public:
  IndicatorLED(){
    setupPins();
  }
  ~IndicatorLED(){}
  void setupPins(){
    /**
     * disconnect led common cathode with ground
     * set all anode pin to zero
     */
    pinMode(ledSwitch,OUTPUT);
    digitalWrite(ledSwitch,LOW);
    pinMode(redPin,OUTPUT);
    pinMode(greenPin,OUTPUT);
    pinMode(bluePin,OUTPUT);
    analogWrite(redPin,0);
    analogWrite(greenPin,0);
    analogWrite(bluePin,0);
  }
  void setColor(Color c){
    analogWrite(redPin,c.r*PWMStep);
    analogWrite(greenPin,c.g*PWMStep);
    analogWrite(bluePin,c.b*PWMStep);
  }
  void turn(int p){
    digitalWrite(ledSwitch,p ? HIGH : LOW);
  }
};
#endif
