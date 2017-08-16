#define DEBUG
const int IN1 = 3;
const int IN2 = 4;
const int EN = 5;
const int pwm = 6;

const int light = 7;

const int UP = 1;
const int DOWN = 2;
// UP & DOWN: #[1/2]$SPEED%
const int STOP = 3;
//STOP: #3$%
const int LIGHT = 4;
//LIGHT: #4$STATE%

//ascii !"#$%&'()*+,-./
const int dataSize = 2;
struct data
{
  int dat[dataSize];
  data()
  {
    memset(dat, 0, sizeof(dat));
  }
  void read()
  {
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
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(light, OUTPUT);
  Serial.begin(9600);
}

void setSpd(int a) //Set Speed
{
  spd = a;
  analogWrite(pwm, spd);
#ifdef DEBUG
  Serial.print("Speed set to ");
  Serial.println(spd);
#endif
}

void setMotor(int state, int sp)
{
  /* * * * * * * *
   *     IN1 IN2 *
   * UP   1   0  *
   * DOWN 0   1  *
   * STOP 0   0  * 
   * * * * * * * */
  digitalWrite(IN1, state == UP ? HIGH : LOW);
  digitalWrite(IN2, state == DOWN ? HIGH : LOW);
  setSpd(sp);
}

int lightState = 0;

const int ON = 1;
const int OFF = 0;

void setLight(int state)
{
  digitalWrite(light, state == ON ? HIGH : LOW);
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
      setMotor(now[0], now[1]);
    else if (isLight(now[0]))
      setLight(now[1]);
  }
}
