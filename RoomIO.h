#ifndef ROOMIO_H
#define ROOMIO_H

#include <string>
class RoomIO {

	static unsigned int maxId;
	const unsigned int id;
	std::string name;

	unsigned int temperatureChannel;
	unsigned int temperature;
	unsigned int lightChannel;
	unsigned int light;
	unsigned int cycleTime;			//Duration between cycle of checking the sensor values

public:

	RoomIO(std::string, unsigned int, unsigned int, unsigned int = 3600);	//name, temperature channel, light channel and cycle time

	const unsigned int getId();
	std::string getName();
	unsigned int getTemperature();
	unsigned int getTemperatureChannel();
	unsigned int getLight();
	unsigned int getLightChannel();
	unsigned int getCycleTime();

	void setName(std::string);
	void setTemperature(unsigned int);
	void setLight(unsigned int);
	void setTemperatureChannel(unsigned int);
	void setLightChannel(unsigned int);
	void setCycleTime(unsigned int);

	std::string log();

};

#endif
