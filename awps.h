#ifndef AWPS_H
#define AWPS_H

#include <vector>
#include "PlantIO.h"
#include "RoomIO.h"

//Defining the pin used and parameters -> Transfer this in a config file?
#define GLEDPIN 3
#define YLEDPIN 4
#define RLEDPIN 5

void initLEDGPIO();
void intHandler(int signum);
int init();
void update(PlantIO*);
void update(RoomIO*);
void waterPlant(PlantIO*);
void work(PlantIO*);
void hibernate(int);
int checkTemperature(int);
int checkLight(int);
void processP(PlantIO*);
void processR(RoomIO*);
void awps(std::vector<PlantIO*>, std::vector<RoomIO*>);
#endif
