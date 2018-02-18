#include <Motor.h>

Motor::Motor(unsigned char _pinPWM, unsigned char _pinDir, unsigned char _pinEnc, bool _isInvert)
{
	pinPWM = _pinPWM;
	pinDir = _pinDir;
	pinEnc = _pinEnc;
	isInvert = _isInvert;
	curDir = 0;
	//lastDir = curDir;
	pinMode(_pinPWM, OUTPUT);
	pinMode(_pinDir, OUTPUT);
	pinMode(_pinEnc, INPUT_PULLUP);
}

float Motor::getSpeedRPM()
{
	if (curDir == 0)
		return speedRPM;
	else
		return -speedRPM;
}

void Motor::setSpeedRPM(float _speedRPM){
	speedRPM = _speedRPM;
}

void Motor::count(){
	enc_count++;
}

void Motor::clear(){
	enc_count = 0;
}

void Motor::computeSpeed(float _time){
	speedRPM = ((float(enc_count) / 1536.0) / (float(_time) / 1000000)) * 60;
	enc_count = 0;
}

void Motor::runPWM(int PWM)
{
	if (isInvert)
		PWM = -PWM;

	if (PWM > 0)
	{
		digitalWrite(pinDir, HIGH);
		if (PWM > 255)
			PWM = 255;
		curDir = 0;
	}
	else if(PWM < 0)
	{
		digitalWrite(pinDir, LOW);
		if (PWM < -255)
			PWM = -255;
		curDir = 1;
	}
	analogWrite(pinPWM, abs(PWM));
}