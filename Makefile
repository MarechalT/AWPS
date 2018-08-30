CXXFLAGS=-Wall -g -std=c++11 #Define CXXFLAGS to automatically add them in the command -g for Valgrind use

SRC=$(wildcard *.cc)
DEPS=$(wildcard *.h)
LDFLAGS=-lwiringPi -lpthread
OUTPUT=bin/
OBJ=$(SRC:.cc=.o)

# Redefine the default command to create executable without suffix (use g++ instead of gcc)
awps: $(OBJ)
	g++ $(LDFLAGS) -o $(OUTPUT)$@ $^

all: awps awps.pdf

awps.pdf: $(SRC) $(DEPS) Makefile
	a2ps -o - $^ | ps2pdf - docs/$@

clean:
	rm -f *~ *.o *.bak
	find bin/ -type f -executable -exec rm '{}' \;

mrproper: clean erasedata

erasedata:
	rm -f data/*.dat

depend:
	makedepend $(sources)
