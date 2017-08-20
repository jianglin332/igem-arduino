#define DEBUG

#include "IndicatorLED.h"

const int N_MOTOR = 3;

const int IN1[N_MOTOR] = {3, 4, A1};
const int IN2[N_MOTOR] = {7, 8, A2};
const int EN[N_MOTOR] = {5, 6, A3};

const int light = A0;


const int ON = 1;
const int OFF = 0;

IndicatorLED *ind;

const int UP = 1;
const int DOWN = 2;
// UP & DOWN: #[1/2]$NO%SPEED&
const int STOP = 3;
//STOP: #3$%
const int LIGHT = 4;
//LIGHT: #4$STATE%

//ascii !"#$%&'()*+,-./
const int dataSize = 3;

struct data
{
  int dat[dataSize];
  data()
  {
    memset(dat, 0, sizeof(dat));
  }
  void read()
  {
    delay(1);
    char nowByte = 0;
    for (int i = 0; i < dataSize; i++)
    {
      char nowCh = '#' + i;
      int num = 0;
      while (Serial.available() > 0 && nowByte != nowCh)
        nowByte = Serial.read();
      while (Serial.available() > 0 && (nowByte = Serial.read()) != nowCh + 1)
        num = num * 10 + nowByte - '0';
      dat[i] = num;
    }
  }
  int operator[](int p)
  {
    return dat[p];
  }
};

unsigned int spd = 0; //Speed
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < N_MOTOR; i++)
  {
    pinMode(IN1[i], OUTPUT);
    pinMode(IN2[i], OUTPUT);
    pinMode(EN[i], OUTPUT);
  }
  ind = new IndicatorLED;
  ind->turn(ON);
  ind->setColor(green);
  pinMode(light, OUTPUT);
  Serial.begin(115200);
}

void setSpd(int a, int no) //Set Speed
{
  spd = a;
  analogWrite(EN[no], spd);
#ifdef DEBUG
  Serial.print("Speed set to ");
  Serial.println(spd);
#endif
}

void setMotor(int state, int no, int sp)
{
  /* * * * * * * *
   *     IN1 IN2 *
   * UP   1   0  *
   * DOWN 0   1  *
   * STOP 0   0  * 
   * * * * * * * */
  digitalWrite(IN1[no], state == UP ? HIGH : LOW);
  digitalWrite(IN2[no], state == DOWN ? HIGH : LOW);
  setSpd(sp, no);
}

int lightState = 0;

void setLight(int state)
{
  digitalWrite(light, state == ON ? HIGH : LOW);
  ind->setColor(state == ON ? red : green);
#ifdef DEBUG
  Serial.print("Light state changed to: ");
  Serial.println(state == ON ? "on" : "off");
#endif
}

bool isMotor(int a)
{
  return a == UP || a == DOWN || a == STOP;
}

bool isLight(int a)
{
  return a == LIGHT;
}
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    data now;
    now.read();
    if (isMotor(now[0]))
      setMotor(now[0], now[1], now[2]);
    else if (isLight(now[0]))
      setLight(now[1]);
  }
}
