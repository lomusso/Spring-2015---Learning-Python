#ifndef Testing_h
#define Testing_h

#include "Arduino.h"

class Testing {
public:
	Testing(int pin);
	void test();
	void calculate_stats;
	float pressure;
	float average_pressure;
	float standard_deviation;
	float coeff_var;
private:
	int _pin;
	float _start_time;
	float _max_pressure;
	float _test_time;
	float _max_value;
	int _max_index;
	float _max_three_values[3] = {0, 0, 0};
	static const float _offset = 0.13;		// zero offset of transducer
	static const int _test_duration = 7500;	// ms
	static const float _scale = 24.7078;	// conversion factor for V to kPa
}