#include "ioManager.h"
#include <wiringPi.h>
#include <ctime>

void initRelay(int pin){
	pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
}

void activateRelay(int pin){
        digitalWrite(pin, HIGH);
}

void desactivateRelay(int pin){
        digitalWrite(pin, LOW);
}

void initLed(int pin){
	pinMode(pin, OUTPUT); 
	digitalWrite(pin, LOW);
}
void turnOn(int pin){
	digitalWrite(pin, HIGH);
}

void turnOff(int pin){
        digitalWrite(pin, LOW);
}

void blink(int pin, int timer){
	time_t current_time,beg_time;
	time(&beg_time);
	time(&current_time);
	while (difftime(current_time,beg_time) < timer){
		digitalWrite (pin, HIGH) ;  // On
		delay (500) ;               // mS
		digitalWrite (pin, LOW) ;   // Off
		delay (500) ;
		time(&current_time);
	}
}

void blinkSeveral(int pin1, int pin2, int pin3){
	turnOn(pin1);
        delay(100) ;               // mS
	turnOff(pin1);
	turnOn(pin2);
	delay(100);
	turnOff(pin2);
	turnOn(pin3);
	delay(100) ;
	turnOff(pin3);
}
