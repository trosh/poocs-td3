#ifndef IMAGE_HH
#define IMAGE_HH

#include "Tableau.hh"
#include "Pixel.hh"

class Image {
protected:
	Tableau<Pixel> _cont;
public:
	pixel(const N2&);
};

#endif // IMAGE_HH
