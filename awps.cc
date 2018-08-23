#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string>
#include <cstdlib>
#include "mcp3008Reading.h"
//#include "archives.h"

using namespace std;

int main(int argc, char* argv[]){
int cycle = 3600;

if(argc == 2){
	cycle = atoi(argv[1]);
}

//string filename("/home/pi/Documents/moisture_sensor_TML/mcp.dat");
int tab[3];

//Setup WiringPi in order to use the library wiringPi

wiringPiSetup();
//pinMode(0,OUTPUT);	//
pinMode(2,OUTPUT);	//Relay control

const int moistureChannel = 5;
const int moistureLimit = 500;


//Initialisation of the Virtual Pins
initMCP3008();

while (1){
	int x = readMCP3008(moistureChannel);
	//double temper = analogRead(BASE+6);
	//cout << "temper = " << temper << endl;
	//temper = temper / 1024 * 3.3 * 10;
	
	struct timeval tod;
	gettimeofday(&tod,NULL);
	tab[0] = tod.tv_sec;

	if (x < moistureLimit){ // The soil is moist enough
	digitalWrite (2,LOW);
	}
	else{
	digitalWrite (2,HIGH);	//We activate the pump
	}

	tab[1] = x;
	tab[2] = 0;
//	tab[2] = (int)temper;
        cout << "time : " << tab[0] << ", Value is: " << tab[1] << ", and T° is : " << tab[2]  << " °C"<< endl;
	
//	saveInFile(filename, tab,(unsigned int)( sizeof(tab)/sizeof(*tab) ));

	struct timeval t;
	t.tv_sec = cycle;
	t.tv_usec=0;
	select(0,NULL,NULL,NULL,&t);

}
cout << "returning 0 " << endl;
return 0;

}
