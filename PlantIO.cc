#include "PlantIO.h"
#include "ioManager.h"
#include "basic_maths.h"
#include <iostream>
#include <string>

PlantIO::PlantIO(std::string n, unsigned int rp,unsigned int ml, unsigned int dl, unsigned int mc, unsigned int wt, unsigned int ct, double mtbw){
        name = n;
        relayPin=rp;
        moistureLimit=ml;
        dryLimit = dl;
        moistureChannel=mc;
        waterTime=wt;
	cycleTime=ct;
	state=0;
	moistureValueQuantity=5;
        moistureValue = new unsigned int [moistureValueQuantity];
	lastWaterTime = 0;
	minTimeBetweenWatering = mtbw;
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
unsigned int PlantIO::getMoistureValue(){
return average(moistureValue,moistureValueQuantity);
}
time_t PlantIO::getLastWaterTime(){
return lastWaterTime;
}
double PlantIO::getMinTimeBetweenWatering(){
return minTimeBetweenWatering;
}

void PlantIO::printAllMoistureValues(){ //Debugging purpose
	for(unsigned int i = 0; i < moistureValueQuantity;i++){
		std::cout << moistureValue[i] << " " ;
	}
	std::cout << std::endl;
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
void PlantIO::setState(unsigned int mv){
	if(mv < moistureLimit)
		state = wet;
	else if(mv >= moistureLimit && mv < dryLimit)
		state = moist;
	else if(mv >= dryLimit)
		state = dry;
	else
		std::cerr << "Wrong Moisture Value passed" << std::endl;
}

void PlantIO::setMoistureValue(unsigned int mv){
	static bool init = true;
	if(init){
		for(unsigned int i = 0; i < moistureValueQuantity;i++)
                	moistureValue[i] = mv;
	init = false;
	}
	else{
	std::cout << "new value is : " << mv << std::endl;
	for(unsigned int i = 0; i < moistureValueQuantity-1;i++)
		moistureValue[i] = moistureValue[i+1];
	moistureValue[moistureValueQuantity - 1] = mv;
	}
	setState(getMoistureValue());
	printAllMoistureValues();
}
void PlantIO::setLastWaterTime(time_t wt){
lastWaterTime = wt;
}
void PlantIO::setMinTimeBetweenWatering(double mtbw){
minTimeBetweenWatering = mtbw;
}

void PlantIO::initGPIO(){
initRelay(relayPin);
}
