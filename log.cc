
#include "log.h"
#include <fstream>
#include <iostream>
//using namespace std;

int saveInFile(std::string filename, int* tab, unsigned int tabSize){
	std::fstream file;
        file.open(filename.c_str(),std::fstream::out | std::ios::app);

        if (file.is_open()){
                for(unsigned int i=0; i < tabSize - 1;i++){
                file << tab[i] << " ";}
                file << tab[tabSize-1];
                file << std::endl;
                file.close();
        }
        else {
                std::cerr << "Unable to open the file " << filename << std::endl;
                return -1;
        }
        return 0;
}
