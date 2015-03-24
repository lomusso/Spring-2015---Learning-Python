#include "Arduino.h"
#include "Testing.h"

Testing::Testing(int pin) {
	pinMode(pin, INPUT);
	_pin = pin;
}

void Testing::test() {
    int start_time = millis(); 
    float max_pressure = 0;
    while(millis() < test_duration + start_time) {  
        pressure = analogRead(_pin); 
        pressure = pressure*(5.0/1023.0) - offset;
        max_pressure = max(max_pressure, pressure);
    }
    pressure = max_pressure*_scale;
    pressure = pressure*100;
}

void Testing::rest() {
	

}      