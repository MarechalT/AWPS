#include "awps.h"
#include <cstdlib>	//atoi()
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
//	Defining Argument possibility to change the time cycle of all plants
	int cycle(0);
	if (argc == 2) {
		cycle = atoi(argv[1]);
	} else
		cycle = 3600;

	if (init()) {
		//Defining the list of plant to follow and their parameters (todo move to a cfg file)
		std::vector<RoomIO*> roomGroup;
		RoomIO* livingRoom = new RoomIO("livingRoom", 0, 3,cycle);
		roomGroup.push_back(livingRoom);
		std::vector<PlantIO*> plantGroup;
		PlantIO* basil = new PlantIO("basil", 2,6,5, 150, 450, 8, cycle);
		PlantIO* kolendra = new PlantIO("kolendra", 0,7,4, 200, 500, 8, 2*cycle);
		plantGroup.push_back(basil);
		plantGroup.push_back(kolendra);

		awps(plantGroup, roomGroup);
	}
	std::cout << "End of program ! " << std::endl;
	return 0;
}
