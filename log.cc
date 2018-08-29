#include "log.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/time.h> //gettimeofday()

using namespace std;

int saveInFile(std::string filename, stringstream& ss){
	std::fstream file;
        file.open(filename.c_str(),std::fstream::out | std::ios::app);

        if (file.is_open()){
		file << ss.rdbuf();
                file.close();
        }
        else {
		file.open(filename.c_str(),std::fstream::out | std::ios::trunc);
		if (file.is_open()){
  	        	file << ss.rdbuf();
                	file.close();
        	}
		else{
		std::cerr << "Unable to open the file " << filename << std::endl;
                return -1;
		}
        }
        return 0;
}

void log(PlantIO* p){

        stringstream ss;
	struct timeval tod;
        gettimeofday(&tod, NULL);
	ss << tod.tv_sec << " " << p->getName() << " " << p->getMoistureValue()  << " " << p->getLastWaterTime() << endl;

	string fileName = "/home/pi/Documents/AWPS/data/";
	unsigned int plantId = p->getId();
	fileName += to_string(plantId) + ".dat";
	saveInFile(fileName, ss);
}
