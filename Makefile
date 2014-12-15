CXX := g++
RM := rm -f

all: main

N2.o: N2.cc N2.hh
	$(CXX) -c $<

main: main.cc Tableau.hh
	$(CXX) -o $@ $<

clean:
	$(RM) main
