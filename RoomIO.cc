#include "RoomIO.h"
#include "ioManager.h"
#include "basic_maths.h"
#include "ServiceTime.h"
#include <iostream>
#include <string>
#include <sstream>

unsigned int RoomIO::maxId = 0;

RoomIO::RoomIO(std::string n, unsigned int tc, unsigned int lc, unsigned int ct) :
		id(maxId++), name(n), temperature(0), light(0), temperatureChannel(tc), lightChannel(lc), cycleTime(ct) {
}

const unsigned int RoomIO::getId() {
	return id;
}
std::string RoomIO::getName() {
	return name;
}
unsigned int RoomIO::getTemperature() {
	return temperature;
}
unsigned int RoomIO::getTemperatureChannel() {
	return temperatureChannel;
}
unsigned int RoomIO::getLight() {
	return light;
}
unsigned int RoomIO::getLightChannel() {
	return lightChannel;
}
unsigned int RoomIO::getCycleTime() {
	return cycleTime;
}

void RoomIO::setName(std::string n) {
	name = n;
}
void RoomIO::setLight(unsigned int l) {
	light = l;
}
void RoomIO::setTemperature(unsigned int t) {
	temperature = t;
}
void RoomIO::setLightChannel(unsigned int lc) {
	lightChannel = lc;
}
void RoomIO::setTemperatureChannel(unsigned int tc) {
	temperatureChannel = tc;
}
void RoomIO::setCycleTime(unsigned int ct) {
	cycleTime = ct;
}

std::string RoomIO::log() {
	std::stringstream ss;
	ss << getCurrentTime() << " " << getName() << " " << getTemperature() << " " << getLight() << std::endl;
	return ss.str();
}
