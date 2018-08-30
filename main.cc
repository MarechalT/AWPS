#include "awps.h"
#include <cstdlib>	//atoi()
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
//	Defining Argument possibility to change the cycle
	int cycle(0);
        if (argc == 2) {
                cycle = atoi(argv[1]);
        } else
                cycle = 3600;

        if (init()) {
	//Defining the list of plant to follow and their parameters (todo move to a cfg file)
	std::vector<PlantIO*> plantGroup;
	PlantIO* basil = new PlantIO("basil",2,150,450,5,8,600);
	PlantIO* kolendra = new PlantIO("kolendra",6,200,500,4,8,1800);
	plantGroup.push_back(basil);
	plantGroup.push_back(kolendra);

	awps(plantGroup);

        }
	std::cout << "End of program ! " << std::endl;
        return 0;
}
