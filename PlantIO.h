#ifndef PLANTIO_H
#define PLANTIO_H

#include <string>
class PlantIO{

	std::string name;
	unsigned int relayPin;
	unsigned int moistureLimit;
	unsigned int dryLimit;
	unsigned int moistureChannel;
	unsigned int waterTime;
	unsigned int cycleTime;
	unsigned int state;
public:

PlantIO(std::string,unsigned int,unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
std::string getName();
unsigned int getRelayPin();
unsigned int getMoistureLimit();
unsigned int getDryLimit();
unsigned int getMoistureChannel();
unsigned int getWaterTime();
unsigned int getCycleTime();
unsigned int getState();


void setName(std::string);
void setRelayPin(unsigned int);
void setMoistureLimit(unsigned int);
void setDryLimit(unsigned int);
void setMoistureChannel(unsigned int);
void setWaterTime(unsigned int);
void setCycleTime(unsigned int);
void setState(unsigned int);

void initGPIO();
};

#endif
