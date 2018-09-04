#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>	//select()
#include <signal.h>	//Unix signals
#include <thread>
#include <wiringPi.h>

#include "awps.h"
#include "mcp3008Reading.h"
#include "ioManager.h"
#include "log.h"
#include "ServiceTime.h"

using namespace std;

const static volatile int keepRunning = 1;

void intHandler(int signum) {
	cout << "Caught signal " << signum << endl;
	cout << "Shutting down the AWPS software" << endl;
	initLEDGPIO();
	exit(signum);
}

void initLEDGPIO() {
	OutputInit(GLEDPIN);
	OutputInit(YLEDPIN);
	OutputInit(RLEDPIN);
}

int init() {
	signal(SIGINT, intHandler);	//Dealing signal like ^C
	wiringPiSetup();	//Initialise the wiringPi Library functions.
	initLEDGPIO();		//Init the GPIO used in this project
	initMCP3008();		//Init the ADC component
	return 1;
}

void update(PlantIO* p) {
	unsigned int x = readMCP3008(p->getMoistureChannel());
	p->setMoistureValue(x);
	p->setState(p->getMoistureValue());
}

void update(RoomIO* r){
	r->setTemperature(checkTemperature(r->getTemperatureChannel()));
	r->setLight(checkLight(r->getLightChannel()));
}

int checkTemperature(int channel) {
	double temper = readMCP3008(channel);
	temper = (temper / 1024 * 3.3 * 100) - 273.15;
	return temper;
}

int checkLight(int channel) {
	double light = readMCP3008(channel);
	//Todo Calibration of the sensor
	return light;
}
bool isWaterPlantPossible(PlantIO* p) {

	if (difftime(getCurrentTime(), p->getLastWaterTime()) > p->getMinTimeBetweenWatering())
		return true;
	else {
		cout << "Watering impossible: The plant was watered not long ago ... still waiting "
				<< p->getMinTimeBetweenWatering() - difftime(getCurrentTime(), p->getLastWaterTime()) << "s" << endl;
	}
	return false;
}
void water(unsigned int pin, unsigned int sec) {
	OutputHighSec(pin, sec, actionNotify);
	OutputHigh (GLEDPIN); // Plant was poured so green light till the next check.
}

void waterPlant(PlantIO* p) {
	if (isWaterPlantPossible(p)) {
		water(p->getRelayPin(), p->getWaterTime());
		p->setLastWaterTime(getCurrentTime());
	} else {
		cout << "Watering Plant impossible" << endl;
	}
}

void work(PlantIO* p) {
	switch (p->getState()) {
	case wet: {
		//Light the Green Led
		OutputHigh(GLEDPIN);
		OutputLow(YLEDPIN);
		OutputLow(RLEDPIN);
		break;
	}
	case moist: {
		//Light the Yellow Led
		OutputLow(GLEDPIN);
		OutputHigh(YLEDPIN);
		OutputLow(RLEDPIN);
		break;
	}
	case dry: {
		//Light the Red Led
		OutputLow(GLEDPIN);
		OutputLow(YLEDPIN);
		OutputHigh(RLEDPIN);
		// Use the pump for WATERTIME s
		waterPlant(p);
		break;
	}
	default:
		cout << "ERROR switch reached default case " << endl;
	}
}

void hibernate(int s) {
	struct timeval t;
	t.tv_sec = s;
	t.tv_usec = 0;
	select(0, NULL, NULL, NULL, &t);
}

void processP(PlantIO* p) {
	while (keepRunning) {
		update(p);
		work(p);
		saveInFile("P_" + p->getId(), p->log());
		hibernate(p->getCycleTime());
	}
}

void processR(RoomIO* r) {
	while (keepRunning) {
		update(r);
		saveInFile("R_" + r->getId(), r->log());
		hibernate(r->getCycleTime());
	}
}

void awps(vector<PlantIO*> plantGroup, vector<RoomIO*> roomGroup) {
	//Create a thread for each plant in order to 'consult' each of them as often as it is specified in the config of each plant
	for (std::vector<PlantIO*>::iterator it = plantGroup.begin();it != plantGroup.end();++it){
		thread(processP,*it).detach();}
	for (std::vector<RoomIO*>::iterator ite = roomGroup.begin();ite != roomGroup.end();++ite){
		thread(processR,*ite).detach();}

	while(keepRunning);
}
