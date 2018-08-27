#ifndef AWPS_H
#define AWPS_H


#include "PlantIO.h"

//Defining the pin used and parameters -> Transfer this in a config file?
#define TEMPERATURECHANNEL 6
#define GLEDPIN 3
#define YLEDPIN 4
#define RLEDPIN 5

//Different states for the state machine
enum state {
	wet, moist, dry
};

void initGPIO();
void intHandler(int signum);
int init();
void checkAndSetState(PlantIO*);
void waterPlant(PlantIO* p);
void work(PlantIO* p);
void log(int state, int temper);
void hibernate(int s);
int checkTemperature();

#endif
