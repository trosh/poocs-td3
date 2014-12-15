CXX := g++
RM := rm -f

all: N2.o main

N2.o: N2.cc N2.hh
	$(CXX) -c $<

main: main.cc Tableau.hh N2.o
	$(CXX) -o $@ N2.o $<

clean:
	$(RM) main
