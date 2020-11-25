#ifndef motorLib_h
#define motorLib_h

class Motor
{
private:
	int _phasePin;
	int _enablePin;
	int _signal1;
	int _signal2;
	int _countVariation = 0;
	int _countsPerRev = 64;
	int _currentAngle = 0;
public:
	Motor(int phasePin, int enablePin, int signal1, int signal2);
	void setSpeed(int speed_);
	void setDutyCycle(int duty_);
	
	updateCounter(int signal_);
	float getAngle();
	float getRadians();
  

	void powerOff();
	void powerOn();

	int phasePin;
	int gearRatio;
	int duty;

	volatile long counter = 0;
};

#endif
