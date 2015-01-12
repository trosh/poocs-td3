#ifndef PIXEL_HH
#define PIXEL_HH

#include <N2.hh>

typedef int col;

class Pixel : public N2 {
protected:
	col _c;
public:
	Pixel();
	Pixel(const int, const int, const col);
	Pixel(const N2&, col);
	~Pixel() {}
	col couleur() const;
	Pixel operator+(const Pixel&) const;
	Pixel operator-(const Pixel&) const;
	Pixel operator/(const int) const;
friend std::ostream&
operator<<(std::ostream&, const Pixel&);
};

#endif // PIXEL_HH
