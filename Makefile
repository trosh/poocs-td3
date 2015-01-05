CXX := g++
CFLAGS := -Wall -Iinclude
RM := rm -f
TARGETS := main pgm_example stress_tableau
OBJECTS := N2.o Pixel.o Triangle.o

.PHONY: all clean purge

all: $(OBJECTS) $(TARGETS)

N2.o: src/N2.cc include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Pixel.o: src/Pixel.cc include/Pixel.hh include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Triangle.o: src/Triangle.cc include/Triangle.hh include/Pixel.hh include/N2.hh
	$(CXX) $(CFLAGS) -c $<

main: src/main.cc include/Tableau.hh $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $(OBJECTS) $<

pgm_example: src/pgm_example.cc
	$(CXX) $(CFLAGS) -o $@ $<

stress_tableau: src/stress_tableau.cc include/stress_data.hh include/Tableau.hh
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJECTS)

purge:
	$(RM) $(TARGETS) $(OBJECTS)
