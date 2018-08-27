#ifndef LEDMANAGER_H
#define LEDMANAGER_H
void activateRelay(int pin);
void desactivateRelay(int pin);
void initLed(int pin);
void initRelay(int pin);
void turnOn(int pin);
void turnOff(int pin);
void blink(int pin,int timer);
void blinkSeveral(int pin, int pin2, int pin3);


#endif
