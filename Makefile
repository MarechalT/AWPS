CXXFLAGS=-Wall -g #Define CXXFLAGS to automatically add them in the command -g for Valgrind use

SRC=$(wildcard *.cc)
DEPS=$(wildcard *.h)
LDFLAGS=-lwiringPi
OBJ=$(SRC:.cc=.o)

# Redefine the default command to create executable without suffix (use g++ instead of gcc)
awps: $(OBJ)
	g++ $(LDFLAGS) -o $@ $^

all: awps awps.pdf

awps.pdf: $(SRC) $(DEPS) Makefile
	a2ps -o - $^ | ps2pdf - docs/$@

clean:
	rm -f *~ *.o *.bak

mrproper: clean
	rm -f awps

erasedata:
	rm -f data/*

depend:
	makedepend $(sources)
