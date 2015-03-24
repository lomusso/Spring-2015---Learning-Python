#ifndef Testing_h
#define Testing_h

#include "Arduino.h"

class Testing {
public:
	Testing(int pin);
	void test();
	float pressure;
private:
	int _pin;
	static const float _offset = 0.13;		// zero offset of transducer
	static const int _test_duration = 7500;	// ms
	static const float _scale = 24.7078;	// conversion factor for V to kPa
}