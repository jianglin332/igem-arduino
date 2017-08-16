#include "IndicatorLED.h"

const int workingLEDSwitch = 3;
IndicatorLED* ind;
bool workingLEDOn = false;

void setupWorkingLED(){
  pinMode(workingLEDSwitch,OUTPUT);
  digitalWrite(workingLEDSwitch,LOW);
 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ind = new IndicatorLED();
  setupWorkingLED();
  ind->setColor(green);
  ind->turnOn();
  pinMode(6,INPUT);
  Serial.println("complete");
}
void turnOnWorkingLED(){
  workingLEDOn = true;
  digitalWrite(workingLEDSwitch,HIGH);
  delay(1);
  ind->setColor(red);
  ind->turnOn();
}
void turnOffWorkingLED(){
  workingLEDOn = false;
  digitalWrite(workingLEDSwitch,LOW);
  delay(1);
  ind->setColor(yellow);
  ind->turnOn();
}
byte incomingByte;
void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0){
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                if(incomingByte == '1'){
                  turnOnWorkingLED();
                }else if (incomingByte == '0'){
                  turnOffWorkingLED();
                }
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
                Serial.println(digitalRead(6),BIN);
                
        }
        
        delay(2);

}
