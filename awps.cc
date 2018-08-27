#include "awps.h"
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>	//select()
//#include <sys/select.h>
#include <sys/time.h>	//gettimeofday()
#include <string>
#include <signal.h>	//Unix signals
#include "mcp3008Reading.h"
#include "ioManager.h"
#include "log.h"
#include "PlantIO.h"
//#include <vector>
//#include "archives.h"

using namespace std;

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
	cout << "checking state" << endl;
	unsigned int x = readMCP3008(p->getMoistureChannel());
	cout << "Sensor value is : " << x << endl;
	if (x <= p->getMoistureLimit()) {
		p->setState(wet);
	} else if (x > p->getMoistureLimit() && x <= p->getDryLimit()) {
		p->setState(moist);
	} else if (x > p->getDryLimit()) {
		p->setState(dry);
	}
}

void waterPlant(PlantIO* p) {
	time_t current_time,beg_time;
        time(&beg_time);
        time(&current_time);
	unsigned int wateringTime = p->getWaterTime();
        activateRelay(p->getRelayPin());
        while (difftime(current_time,beg_time) < wateringTime){
		blinkSeveral(RLEDPIN,YLEDPIN,GLEDPIN);
		time(&current_time);
		}
	desactivateRelay(p->getRelayPin());
	turnOn(GLEDPIN); // Plant was poured so green light till the next check.
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

void log(int state, int temper) {
	//Path for the logFILE
	string filename("~/Documents/AWPS/awps.data");
	//Tab to log in a file

	int tab[3];
	struct timeval tod;
	gettimeofday(&tod, NULL);
	tab[0] = tod.tv_sec;
	tab[1] = state;
	tab[2] = temper;
	cout << "time : " << tab[0] << ", state is: " << tab[1] << ", and T° is : " << tab[2] << " °C" << endl;
	//      saveInFile(filename, tab,(unsigned int)( sizeof(tab)/sizeof(*tab) ));
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
