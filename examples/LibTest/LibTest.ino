#include <motorLib.h>

const int phasePin = 6;
const int enablePin = 7;
const int signal1 = 21;
const int signal2 = 20;

const int gearRatio = 131;


Motor motor(phasePin, enablePin, signal1, signal2);

void setup() {
  Serial.begin(9600);
  initMotor();
}

void loop() {
  Serial.println(motor.getAngle());
  motor.setSpeed(10);
  motor.setDutyCycle(10);
}

void initMotor()
{
  attachInterrupt(digitalPinToInterrupt(signal1), signal1Change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(signal2), signal2Change, CHANGE);
  motor.gearRatio = gearRatio;
}

void signal1Change()
{
  motor.updateCounter(signal1);
}
void signal2Change()
{
  motor.updateCounter(signal2);
}
