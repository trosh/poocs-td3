CXX := g++
CFLAGS := -Wall -Iinclude -g
RM := rm -f
TARGETS := main test stress_tableau
OBJECTS := N2.o Pixel.o Triangle.o Image.o Cavite.o Maillage.o

.PHONY: all clean purge cr

all: $(OBJECTS) $(TARGETS)

N2.o: src/N2.cc include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Pixel.o: src/Pixel.cc include/Pixel.hh include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Triangle.o: src/Triangle.cc include/Triangle.hh include/Pixel.hh \
            include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Image.o: src/Image.cc include/Image.hh include/Pixel.hh include/N2.hh
	$(CXX) $(CFLAGS) -c $<

Cavite.o: src/Cavite.cc include/Pixel.hh include/N2.hh
	$(CXX) $(CFLAGS) -c $< -lm

Maillage.o: src/Maillage.cc include/Maillage.hh include/Cavite.hh \
            include/Tableau.hh include/Triangle.hh include/Pixel.hh \
            include/N2.hh include/Image.hh
	$(CXX) $(CFLAGS) -c $< -lm

main: src/main.cc include/Tableau.hh $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $(OBJECTS) $< -lm

test: src/test.cc include/Tableau.hh $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $(OBJECTS) $<

stress_tableau: src/stress_tableau.cc include/stress_data.hh \
                include/Tableau.hh
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJECTS)

purge:
	$(RM) $(TARGETS) $(OBJECTS)

cr:
	groff -D utf-8 -p -e -ms cr/cr.ms | ps2pdf - > cr/cr.pdf
	evince cr/cr.pdf 2> /dev/null &
