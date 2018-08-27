#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string>
#include <cstdlib>
#include <signal.h>
#include "mcp3008Reading.h"

//#include "archives.h"

#define MOISTURECHANNEL 5
#define TEMPERATURECHANNEL 6
#define MOISTURELIMIT 300
#define DRYLIMIT 500
#define RELAYPIN 2
#define GLEDPIN 3
#define YLEDPIN 4
#define RLEDPIN 5
#define WATERTIME 20

enum state {
	wet, moist, dry
};

using namespace std;
static volatile int keepRunning = 1;
void initGPIO();

void intHandler(int signum) {
	cout << "Caught signal " << signum << endl;
	cout << "Shutting down the AWPS software" << endl;
	initGPIO();
	exit(signum);
}

void initGPIO(){
	pinMode(RELAYPIN, OUTPUT);      //Relay Control pin.
        pinMode(RLEDPIN, OUTPUT);      //Relay Control pin.
        pinMode(YLEDPIN, OUTPUT);      //Relay Control pin.
        pinMode(GLEDPIN, OUTPUT);      //Relay Control pin.
        digitalWrite(RELAYPIN, LOW);
        digitalWrite(GLEDPIN, LOW);
        digitalWrite(YLEDPIN, LOW);
        digitalWrite(RLEDPIN, LOW);
}

int init() {
	//Dealing signal like ^C
	signal(SIGINT, intHandler);
	//Defining port and loop period.
	wiringPiSetup();	//Initialise the wiringPi Library functions.
	initGPIO();
	initMCP3008();
	return 1;
}

int checkstate() {
	cout << "checking state" << endl;
	int x = readMCP3008(MOISTURECHANNEL);
	cout << "Sensor value is : " << x << endl;
	if (x <= MOISTURELIMIT) {
		return wet;
	} else if (x > MOISTURELIMIT && x <= DRYLIMIT) {
		return moist;
	} else if (x > DRYLIMIT) {
		return dry;
	}
	else return -1;
}

void activateRelay(int sec) {
	cout << "activating relay" << endl;
	digitalWrite(RELAYPIN, HIGH);
	struct timeval t;
	t.tv_sec = sec;
	t.tv_usec = 0;
	select(0, NULL, NULL, NULL, &t);
	digitalWrite(RELAYPIN, LOW);
}

void work(int st) {

	switch (st) {
	case wet: {
		//Light the Green Led
		digitalWrite(GLEDPIN, HIGH);
		digitalWrite(YLEDPIN, LOW);
		digitalWrite(RLEDPIN, LOW);
		break;
	}
	case moist: {
		//Light the Yellow Led
		digitalWrite(GLEDPIN, LOW);
		digitalWrite(YLEDPIN, HIGH);
		digitalWrite(RLEDPIN, LOW);
		break;
	}
	case dry: {
		//Light the Red Led
		digitalWrite(GLEDPIN, LOW);
		digitalWrite(YLEDPIN, LOW);
		digitalWrite(RLEDPIN, HIGH);
		// Use the pump for 20 s
		activateRelay(WATERTIME);
		break;
	}
	default:
		cout << "ERROR switch reached default case " << endl;
	}
}

void log(int state, int temper) {
	//string filename("~/Documents/moisture_sensor_TML/mcp.dat");
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

int main(int argc, char* argv[]) {
	int cycle(0);
	if (argc == 2) {
		cycle = atoi(argv[1]);
	} else
		cycle = 3600;

	if (init()) {
		while (keepRunning) {
			int st = checkstate();
			if (st<0)
			cout << "ERROR on the state process" << endl;
			int temper = checkTemperature();
			work(st);
			log(st,temper);
			hibernate(cycle);
		}
	}

	cout << "End of program ! " << endl;
	return 0;

}
