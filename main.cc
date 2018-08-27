#include "awps.h"
#include <cstdlib>	//atoi()
#include <iostream>
static volatile int keepRunning = 1;

int main(int argc, char* argv[]) {
   	int cycle(0);
        if (argc == 2) {
                cycle = atoi(argv[1]);
        } else
                cycle = 86400;

        if (init()) {
      PlantIO* basil = new PlantIO("basil",2,150,450,5,8,cycle);
        //todo Loop on all plants.
        //vector<PlantIO> plantGroup;
        //plantGroup.push_back(basil);
                while (keepRunning) {

                        checkAndSetState(basil);
                        if (basil->getState()<0)
                        std::cout << "ERROR on the state process" << std::endl;
                        int temper = checkTemperature();
                        work(basil);
                        std::cout << "name = " << basil->getName() << std::endl;
                        hibernate(basil->getCycleTime());
                }
        }

	std::cout << "End of program ! " << std::endl;
        return 0;

}
