#include "ioManager.h"
#include <wiringPi.h>
#include "ServiceTime.h"
#include "awps.h"
void OutputInit(int pin) {
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

void OutputHigh(int pin) {
	digitalWrite(pin, HIGH);
}

void OutputHighSec(int pin, unsigned int sec, void (*f)()) {
	time_t beg_time;
	time(&beg_time);
	OutputHigh(pin);
	while (difftime(getCurrentTime(), beg_time) < sec) {
		(*f)();
	}
	OutputLow(pin);
}
void OutputLow(int pin) {
	digitalWrite(pin, LOW);
}

void InputInit(int pin) {
	pinMode(pin, INPUT);
}

void InputRead(int pin) {
	digitalRead(pin);
}

void blink(int pin, int timer) {
	time_t beg_time;
	time(&beg_time);
	while (difftime(getCurrentTime(), beg_time) < timer) {
		OutputHigh(pin);  // On
		delay(500);               // mS
		OutputLow(pin);   // Off
		delay(500);
	}
}
void blinkSeveral(int pin1, int pin2, int pin3) {
	OutputHigh(pin1);
	delay(100);               // mS
	OutputLow(pin1);
	OutputHigh(pin2);
	delay(100);
	OutputLow(pin2);
	OutputHigh(pin3);
	delay(100);
	OutputLow(pin3);
}
void actionNotify() {
	blinkSeveral(RLEDPIN, YLEDPIN, GLEDPIN);
}
