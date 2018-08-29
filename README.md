# AWPS
Automatic Watering Plant system.

The project is based on a Raspberry Pi version B, using RASPBIAN 9 (stretch), kernel 4.14.

Regarding the electronics parts involved we have:
  A power Supply
  A Raspberry Pi version B
  A Prototype Board
  Several Moisture sensors
  One ADC (MCP3008)
  One temperature sensor
  3 LED (1 Green, 1 Yellow, 1 Red)
  3 resistors (75 Ohm)
  1 Transistor N2222
  1 Relay Module
  1 Pump + Pipe
  Wires

GOAL:
  the goal of the project is to be able to water plants while being away from home. Several possibilities can be defined:
  Watering the plants through a webserver page.
  Watering plants using a watchdog and parameters we set, the plant will then "ask" to be watered.

Getting Started
  These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See     deployment for notes on how to deploy the project on a live system.

Prerequisites
  You need to install wiringPi, a library made by Gordon@Drogon. He explains everything on his website. https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/
  Set up SPI on your project, once again thanks to Mr. Gordon.
  https://projects.drogon.net/understanding-spi-on-the-raspberry-pi/
  
Give examples
  $git clone https://github.com/MarechalT/AWPS.git
  $cd AWPS
  $make
  
  The software will be AWPS/bin/awps

  You should definitely configure the different plants on the .config file before starting the application

  To run the software at boot you can copy the AWPS/docs/AWPS.service file in your /etc/systemd/system/ folder and adapt it to your user   and path to the software.
  While running the software will save data in the AWPS/data/ folder. It will also show some values on the Output but it is not relevant   here. You can see the structure of the data files in data/README_datastructure
  While running you can see if there is any error appearing on the console output.

Running the tests
  You can test the software by providing an int as an argument to determine the cycle of reading and decision making.
  example: 
  $./awps 10 to have a 10s loop cycle.

Software used:
  nano
  make
  g++

Versioning
I used git for versioning. For the versions available, see the tags on this repository.

Authors
Thibault MARECHAL
See also the list of contributors who participated in this project.

License
This project is licensed under the MIT License - see the LICENSE.md file for details

Acknowledgments
Jeremy Blythe https://computers.tutsplus.com/tutorials/build-a-raspberry-pi-moisture-sensor-to-monitor-your-plants--mac-52875
