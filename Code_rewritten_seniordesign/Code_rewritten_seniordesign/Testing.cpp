#include "Arduino.h"
#include "Testing.h"

Testing::Testing(int pin) {
	pinMode(pin, INPUT);
	_pin = pin;
}

void Testing::test() { 
    _max_pressure = 0;
    _test_time = 0;
    _start_time = millis();
    while(_test_time < test_duration + start_time) {  
    	_test_time = millis();
        pressure = analogRead(_pin); 
        pressure = pressure*(5.0/1023.0) - offset;
        max_pressure = max(max_pressure, pressure);
    }
    pressure = max_pressure*_scale*100;
}

void Testing::calculate_stats() {
	// Find the three maximum pressure values.
	_max_value = 0;
	for (int i = 0; i < number_trials; i++) {
		if (pressure_values[i] > _max_value) {
			_max_value = pressure_values[i];
			_max_index = i;
		}
	}
	_max_three_values[0] = _max_value;
	pressure_values[_max_index] = 0;

	_max_value = 0;
	for (int i = 0; i < number_trials; i++) {
		if (pressure_values[i] > _max_value) {
			_max_value = pressure_values[i];
			_max_index = i;
		}
	}
	_max_three_values[1] = _max_value;
	pressure_values[_max_index] = 0;

	_max_value = 0;
	for (int i = 0; i < number_trials; i++) {
		if (pressure_values[i] > _max_value) {
			_max_value = pressure_values[i];
			_max_index = i;
		}
	}
	_max_three_values[2] = _max_value;

	// Calculate the average pressure.
	average_pressure = (_max_three_values[0] + _max_three_values[1] + _max_three_values[2])/3.0;

	// Calculate the standard deviation.
	standard_deviation = 0;
	for (int i = 0; i < 3; i++) {
		standard_deviation = standard_deviation + (((_max_three_values[i] - average_pressure)*(_max_three_values[i] - average_pressure))/3);
	}
	standard_deviation = sqrt(standard_deviation);

	// Calculate the coefficient of variation.
	coeff_var = standard_deviation/average_pressure;
}    