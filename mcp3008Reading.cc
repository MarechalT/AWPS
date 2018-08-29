#include <wiringPi.h>
#include <mcp3004.h>
#include "mcp3008Reading.h"
using namespace std;

#define BASE 100
#define SPI_CHAN 1

int initMCP3008(){
	return mcp3004Setup(BASE,SPI_CHAN);
}

int readMCP3008(int channel){
	int value = analogRead(BASE+channel);
	return value;
}
