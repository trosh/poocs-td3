CXX := g++
CFLAGS := -Wall -Iinclude -g
RM := rm -f
TARGETS := main stress_tableau #pgm_example
OBJECTS := N2.o Pixel.o Triangle.o Image.o

.PHONY: all clean purge

all: $(OBJECTS) $(TARGETS)

N2.o: src/N2.cc include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Pixel.o: src/Pixel.cc include/Pixel.hh include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Triangle.o: src/Triangle.cc include/Triangle.hh include/Pixel.hh include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Image.o: src/Image.cc include/Image.hh include/Pixel.hh include/N2.hh
	$(CXX) $(CFLAGS) -c $<

main: src/main.cc include/Tableau.hh $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $(OBJECTS) $<

#pgm_example: src/pgm_example.cc
#	$(CXX) $(CFLAGS) -o $@ $<

stress_tableau: src/stress_tableau.cc include/stress_data.hh include/Tableau.hh
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJECTS)

purge:
	$(RM) $(TARGETS) $(OBJECTS)
