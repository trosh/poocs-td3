CXX := g++
RM := rm -f
OBJECTS := N2.o Pixel.o

.PHONY: all clean purge

all: $(OBJECTS) main

N2.o: N2.cc N2.hh
	$(CXX) -c $<

Pixel.o: Pixel.cc Pixel.hh N2.hh
	$(CXX) -c $<

main: main.cc Tableau.hh $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $<

clean:
	$(RM) $(OBJECTS)

purge:
	$(RM) main $(OBJECTS)
