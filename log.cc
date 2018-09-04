#include <fstream>
#include <iostream>
#include <sstream>

#include "log.h"
#include "ServiceTime.h"
using namespace std;

const string dataPath = "/home/pi/Documents/AWPS/data/";

int saveInFile(std::string fileName, string s) {
	std::fstream file;
	string filename = dataPath + fileName;
	file.open(filename.c_str(), std::fstream::out | std::ios::app);

	if (file.is_open()) {
		cout << s << endl;
		file << s;
		file.close();
	} else {
		file.open(filename.c_str(), std::fstream::out | std::ios::trunc);
		if (file.is_open()) {
			file << s;
			file.close();
		} else {
			std::cerr << "Unable to open the file " << filename << std::endl;
			return -1;
		}
	}
	return 0;
}
