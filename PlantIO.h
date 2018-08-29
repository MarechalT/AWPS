#ifndef PLANTIO_H
#define PLANTIO_H
#include <ctime>
#include <string>
//Different states for the soil
enum state {
        wet, moist, dry
};


class PlantIO{

	static unsigned int maxId;
	const unsigned int id;
	std::string name;
	unsigned int relayPin;
	unsigned int moistureLimit;
	unsigned int dryLimit;
	unsigned int moistureChannel;
	unsigned int waterTime;
	unsigned int cycleTime;
	unsigned int state;
	unsigned int* moistureValue;
	unsigned int moistureValueQuantity;
	time_t lastWaterTime;
	double minTimeBetweenWatering;
public:

PlantIO(std::string,unsigned int,unsigned int, unsigned int, unsigned int, unsigned int = 8, unsigned int = 3600, double = 86400);

const unsigned int getId();
std::string getName();
unsigned int getRelayPin();
unsigned int getMoistureLimit();
unsigned int getDryLimit();
unsigned int getMoistureChannel();
unsigned int getWaterTime();
unsigned int getCycleTime();
unsigned int getState();
unsigned int getMoistureValue();
time_t getLastWaterTime();
double getMinTimeBetweenWatering();

void printAllMoistureValues();

void setName(std::string);
void setRelayPin(unsigned int);
void setMoistureLimit(unsigned int);
void setDryLimit(unsigned int);
void setMoistureChannel(unsigned int);
void setWaterTime(unsigned int);
void setCycleTime(unsigned int);
void setState(unsigned int);
void setMoistureValue(unsigned int);
void initGPIO();
void setLastWaterTime(time_t);
void setMinTimeBetweenWatering(double);
};

#endif
