#ifndef IO_MANAGER_H
#define IO_MANAGER_H

void OutputInit(int pin);
void OutputHigh(int pin);
void OutputHighSec(int pin, unsigned int sec, void (*f)(void));
void OutputLow(int pin);
void InputInit(int pin);
void InputRead(int pin);
void blink(int pin, int timer);
void blinkSeveral(int pin, int pin2, int pin3);
void actionNotify();

#endif
