#ifndef PLANTIO_H
#define PLANTIO_H

#include <ctime>
#include <string>

//Different states for the soil
enum state {
	wet, moist, dry
};

class PlantIO {
	//Id.
	static unsigned int maxId;
	const unsigned int id;
	std::string name;
//Configurations:
	//Hardware Settings
	unsigned int relayPin; 		//Pin which controls the pump
	unsigned int manualWaterPin; //Pin where the manual water button is
	unsigned int moistureChannel;	//Channel used on the ADC converter
	//Software Settings
	unsigned int moistLimit;		//Limit to determine between wet and moist
	unsigned int dryLimit;			//Limit to determine state between moist and dry
	unsigned int waterTime;			//Time the pump will be running (TODO make calculation of pump "speed" to set the value in mL)
	unsigned int cycleTime;			//Duration between cycle of checking the sensor values
	unsigned int state;				//State of the Plant (wet, moist or dry)
	unsigned int* moistureValue;	//Tab of unsigned int, the last 5 value read
	unsigned int moistureValueQuantity;	//Number of unsigned int in the moistureValue Tab
	time_t lastWaterTime;			//Time of the last watering event
	double minTimeBetweenWatering;	//Minimum time to respect before another watering action can occur
public:
	PlantIO(std::string, unsigned int, unsigned int, unsigned int, unsigned int = 100, unsigned int = 400, unsigned int = 8, unsigned int = 3600,
			double = 86400);
	const unsigned int getId();
	std::string getName();

	unsigned int getRelayPin();
	unsigned int getManualWaterPin();
	unsigned int getMoistureChannel();

	unsigned int getMoistLimit();
	unsigned int getDryLimit();
	unsigned int getWaterTime();
	unsigned int getCycleTime();
	unsigned int getState();
	unsigned int getMoistureValue();
	time_t getLastWaterTime();
	double getMinTimeBetweenWatering();

	void printAllMoistureValues(); // TODO remove after full debugging
	void initIO();

	void setName(std::string);

	void setRelayPin(unsigned int);
	void setManualWaterPin(unsigned int);
	void setMoistureChannel(unsigned int);

	void setMoistLimit(unsigned int);
	void setDryLimit(unsigned int);
	void setWaterTime(unsigned int);
	void setCycleTime(unsigned int);
	void setState(unsigned int);
	void setMoistureValue(unsigned int);
	void setLastWaterTime(time_t);
	void setMinTimeBetweenWatering(double);

	std::string log();
};
#endif
