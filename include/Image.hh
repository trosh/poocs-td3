#ifndef IMAGE_HH
#define IMAGE_HH

#include <Pixel.hh>

enum {
	badCoord
} ImageError;

class Image {
protected:
	int _w;
	int _h;
	Pixel * _cont;
public:
	Image();
	Image(int, int);
	Image(const PGMImage&);
	~Image();
	pixel(const N2&) const;
	pixel(const int&, const int&) const;
	nbLignes() const;
	nbColonnes() const;
};

#endif // IMAGE_HH
