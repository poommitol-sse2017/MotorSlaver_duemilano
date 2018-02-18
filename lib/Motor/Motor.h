/*
    Embeded Software Systems Project 2018, TGGS, KMUTNB
    
    MotorSlaver Configuration files for Meccanum Platform Robot,
    
    Auther, Mix, Bekty
*/
#ifndef Motor_H
#define Motor_H
#include "Arduino.h"



class Motor
{
public:
	Motor(unsigned char _pinPWM, unsigned char _pinDir, unsigned char _pinEnc, bool _isInvert);
	void runPWM(int PWM);
	float getSpeedRPM();
	void setSpeedRPM(float _speedRPM);
	void count();
	void clear();
	void computeSpeed(float _time);
	int enc_count = 0;
private:
	bool isInvert = false;
	unsigned char pinPWM;
	unsigned char pinDir;
	unsigned char pinEnc;
	unsigned int curDir;
	//unsigned int lastDir;
	
	float speedRPM; // current PWM
	
	
};

#endif