#include "PlantIO.h"
#include "ioManager.h"
#include "basic_maths.h"
#include "ServiceTime.h"
#include <iostream>
#include <sstream>

unsigned int PlantIO::maxId = 0;

PlantIO::PlantIO(std::string n, unsigned int rp, unsigned int mwp, unsigned int mc, unsigned int ml, unsigned int dl, unsigned int wt,
		unsigned int ct, double mtbw) :
		id(maxId++), name(n), relayPin(rp),manualWaterPin(mwp), moistureChannel(mc), moistLimit(ml), dryLimit(dl), waterTime(wt), cycleTime(ct), state(0), lastWaterTime(
				0), minTimeBetweenWatering(mtbw) {

	moistureValueQuantity = 5;
	moistureValue = new unsigned int[moistureValueQuantity];
}

const unsigned int PlantIO::getId() {
	return id;
}

std::string PlantIO::getName() {
	return name;
}
unsigned int PlantIO::getRelayPin() {
	return relayPin;
}
unsigned int PlantIO::getManualWaterPin() {
	return manualWaterPin;
}

unsigned int PlantIO::getMoistLimit() {
	return moistLimit;
}
unsigned int PlantIO::getDryLimit() {
	return dryLimit;
}
unsigned int PlantIO::getMoistureChannel() {
	return moistureChannel;
}
unsigned int PlantIO::getWaterTime() {
	return waterTime;
}
unsigned int PlantIO::getCycleTime() {
	return cycleTime;
}
unsigned int PlantIO::getState() {
	return state;
}
unsigned int PlantIO::getMoistureValue() {
	return average(moistureValue, moistureValueQuantity);
}
time_t PlantIO::getLastWaterTime() {
	return lastWaterTime;
}
double PlantIO::getMinTimeBetweenWatering() {
	return minTimeBetweenWatering;
}

void PlantIO::printAllMoistureValues() { //Debugging purpose
	for (unsigned int i = 0; i < moistureValueQuantity; i++) {
		std::cout << moistureValue[i] << " ";
	}
	std::cout << std::endl;
}

void PlantIO::setName(std::string n) {
	name = n;
}
void PlantIO::setRelayPin(unsigned int rp) {
	relayPin = rp;
}
void PlantIO::setManualWaterPin(unsigned int mwp) {
	manualWaterPin = mwp;
}
void PlantIO::setMoistLimit(unsigned int ml) {
	moistLimit = ml;
}
void PlantIO::setDryLimit(unsigned int dl) {
	dryLimit = dl;
}
void PlantIO::setMoistureChannel(unsigned int mc) {
	moistureChannel = mc;
}
void PlantIO::setWaterTime(unsigned int wt) {
	waterTime = wt;
}
void PlantIO::setCycleTime(unsigned int ct) {
	cycleTime = ct;
}
void PlantIO::setState(unsigned int mv) {
	if (mv < moistLimit)
		state = wet;
	else if (mv >= moistLimit && mv < dryLimit)
		state = moist;
	else if (mv >= dryLimit)
		state = dry;
	else
		std::cerr << "Wrong Moisture Value passed" << std::endl;
}

void PlantIO::setMoistureValue(unsigned int mv) {
	static bool init = true;
	if (init) {
		for (unsigned int i = 0; i < moistureValueQuantity; i++)
			moistureValue[i] = mv;
		init = false;
	} else {
		std::cout << "new value is : " << mv << std::endl;
		for (unsigned int i = 0; i < moistureValueQuantity - 1; i++)
			moistureValue[i] = moistureValue[i + 1];
		moistureValue[moistureValueQuantity - 1] = mv;
	}
}
void PlantIO::setLastWaterTime(time_t wt) {
	lastWaterTime = wt;
}
void PlantIO::setMinTimeBetweenWatering(double mtbw) {
	minTimeBetweenWatering = mtbw;
}

void PlantIO::initIO() {
	OutputInit(relayPin);
	InputInit(manualWaterPin);
}

std::string PlantIO::log() {
	std::stringstream ss;
	ss << getCurrentTime() << " " << getName() << " " << getMoistureValue() << " " << getLastWaterTime() << std::endl;
	return ss.str();
}
