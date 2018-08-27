#include "PlantIO.h"
#include "ioManager.h"
#include <string>

PlantIO::PlantIO(std::string n, unsigned int rp,unsigned int ml, unsigned int dl, unsigned int mc, unsigned int wt=8, unsigned int ct= 86400){
        name = n;
        relayPin=rp;
        moistureLimit=ml;
        dryLimit = dl;
        moistureChannel=mc;
        waterTime=wt;
	cycleTime=ct;
	state=0;
        }


std::string PlantIO::getName(){
	return name;
}
unsigned int PlantIO::getRelayPin(){
return relayPin;
}
unsigned int PlantIO::getMoistureLimit(){
return moistureLimit;
}
unsigned int PlantIO::getDryLimit(){
return dryLimit;
}
unsigned int PlantIO::getMoistureChannel(){
return moistureChannel;
}
unsigned int PlantIO::getWaterTime(){
return waterTime;
}
unsigned int PlantIO::getCycleTime(){
return cycleTime;
}
unsigned int PlantIO::getState(){
return state;
}

void PlantIO::setName(std::string n){
name = n;
}
void PlantIO::setRelayPin(unsigned int rp){
relayPin = rp;
}
void PlantIO::setMoistureLimit(unsigned int ml){
moistureLimit = ml;
}
void PlantIO::setDryLimit(unsigned int dl){
dryLimit = dl;
}
void PlantIO::setMoistureChannel(unsigned int mc){
moistureChannel = mc;
}
void PlantIO::setWaterTime(unsigned int wt){
waterTime = wt;
}
void PlantIO::setCycleTime(unsigned int ct){
cycleTime = ct;
}
void PlantIO::setState(unsigned int st){
state = st;
}

void PlantIO::initGPIO(){
initRelay(relayPin);
}
