#include "awps.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>	//select()
#include <signal.h>	//Unix signals
#include <thread>
#include <wiringPi.h>

#include "mcp3008Reading.h"
#include "ioManager.h"
#include "log.h"
#include "PlantIO.h"

using namespace std;

static volatile int keepRunning = 1;


void intHandler(int signum) {
	cout << "Caught signal " << signum << endl;
	cout << "Shutting down the AWPS software" << endl;
	initGPIO();
	exit(signum);
}

void initGPIO(){
	initLed(GLEDPIN);
	initLed(YLEDPIN);
	initLed(RLEDPIN);
}

int init() {
	//Dealing signal like ^C
	signal(SIGINT, intHandler);
	wiringPiSetup();	//Initialise the wiringPi Library functions.
	initGPIO();		//Init the GPIO used in this project
	initMCP3008();		//Init the DAC component
	return 1;
}

void checkAndSetState(PlantIO* p) {
	unsigned int x = readMCP3008(p->getMoistureChannel());
	p->setMoistureValue(x);
}

void waterPlant(PlantIO* p) {
	time_t current_time,beg_time;
        time(&current_time);

	if(difftime(current_time,p->getLastWaterTime()) > p->getMinTimeBetweenWatering()){
        	time(&beg_time);
		unsigned int wateringTime = p->getWaterTime();
       		activateRelay(p->getRelayPin());
        	while (difftime(current_time,beg_time) < wateringTime){
			blinkSeveral(RLEDPIN,YLEDPIN,GLEDPIN);
			time(&current_time);
			}
		desactivateRelay(p->getRelayPin());
		turnOn(GLEDPIN); // Plant was poured so green light till the next check.
		p->setLastWaterTime(current_time);
	}
	else{
	cout << "The plant was watered not long ago ... still waiting " << p->getMinTimeBetweenWatering() - difftime(current_time,p->getLastWaterTime()) << "s" << endl;
	}
}

void work(PlantIO* p) {
	switch (p->getState()) {
	case wet: {
		//Light the Green Led
		turnOn(GLEDPIN);
		turnOff(YLEDPIN);
                turnOff(RLEDPIN);
		break;
	}
	case moist: {
		//Light the Yellow Led
                turnOff(GLEDPIN);
                turnOn(YLEDPIN);
                turnOff(RLEDPIN);
		break;
	}
	case dry: {
		//Light the Red Led
                turnOff(GLEDPIN);
                turnOff(YLEDPIN);
                turnOn(RLEDPIN);
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

int checkTemperature() {
	double t = readMCP3008(TEMPERATURECHANNEL);
	//cout << "temper = " << temper << endl;
	//temper = temper / 1024 * 3.3 * 10;
	return t;
}

int checkLight() {
	double l = readMCP3008(LIGHTCHANNEL);
	return l;
}

void process(PlantIO* p){
	while(keepRunning){
		checkAndSetState(p);
        	if ((p)->getState()<0)
        	        std::cout << "ERROR on the state process" << std::endl;
        	work(p);
        	log(p);
		hibernate(p->getCycleTime());
	}
}

void awps(vector<PlantIO*> plantGroup){
	//Create a thread for each plant in order to 'consult' each of them as often as it is specified in the config of each plant
	vector<thread> threads;
       	for (std::vector<PlantIO*>::iterator it = plantGroup.begin();it != plantGroup.end();++it){
		string s = "Thread " + to_string(std::distance(plantGroup.begin(),it));
                thread(process,*it).detach();
	}
	while(keepRunning);
}
