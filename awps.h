#ifndef AWPS_H
#define AWPS_H


#include "PlantIO.h"

//Defining the pin used and parameters -> Transfer this in a config file?
#define TEMPERATURECHANNEL 6
#define GLEDPIN 3
#define YLEDPIN 4
#define RLEDPIN 5

void initGPIO();
void intHandler(int signum);
int init();
void checkAndSetState(PlantIO*);
void waterPlant(PlantIO* p);
void work(PlantIO* p);
void hibernate(int s);
int checkTemperature();

#endif
