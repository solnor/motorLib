#include "Arduino.h"
#include "motorLib.h"

//Constructor. Starts the motor.
//Takes in phase pin, enable pin, and signal pins 
Motor::Motor(int phase, int enable, int signal1, int signal2)
{
  _phasePin = phase;
  _enablePin = enable;
  _signal1 = signal1;
  _signal2 = signal2;
  
  pinMode(_enablePin, OUTPUT);
  powerOn();
}

//Sets the speed of the motor
void Motor::setSpeed(int speed_)
{
	if(speed_ > 127 || speed_ < -127)
	{
		speed_ = 127;
	}
	duty = 127 + speed_;
	analogWrite(_phasePin, duty);
}

//Sets the duty cycle of the motor
void Motor::setDutyCycle(int duty_)
{
	if(duty_ > 255)
	{
		duty_ = 255;
	}
	else if(duty_ < 0)
	{
		duty_ = 0;
	}
	duty = duty_;
	analogWrite(_phasePin, duty);
}

//The signal parameter is which signal changed on the encoder
Motor::updateCounter(int signal_)
{
  if (signal_ == _signal1)
  {
    _countVariation = (digitalRead(_signal2) == HIGH && digitalRead(_signal1) == LOW) || (digitalRead(_signal2) == LOW && digitalRead(_signal1) == HIGH) ? 1 : -1; 
  }
  else if (signal_ == _signal2)
  {
    _countVariation = (digitalRead(_signal1) == HIGH && digitalRead(_signal2) == LOW) || (digitalRead(_signal1) == LOW && digitalRead(_signal2) == HIGH) ? -1 : 1;
  }
  counter += _countVariation;
}

//Gets current angle of the load
float Motor::getAngle()
{
  return float(360.0*counter/_countsPerRev/gearRatio);
}

//Gets current angle of the load in radians
float Motor::getRadians()
{
  return float(2*PI*counter/_countsPerRev/gearRatio);
}

void Motor::powerOff()
{
  digitalWrite(_enablePin, LOW);
}

void Motor::powerOn()
{
  digitalWrite(_enablePin, HIGH);
}
