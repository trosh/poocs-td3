#ifndef IMAGE_HH
#define IMAGE_HH

#include <Tableau.hh>
#include <Pixel.hh>

enum {
	badCoord
} ImageError;

class Image {
protected:
	int _w;
	int _h;
	Tableau<Pixel> _cont;
public:
	pixel(const N2&) const;
	pixel(const int&, const int&) const;
	nbLignes() const;
	nbColonnes() const;
};

#endif // IMAGE_HH
