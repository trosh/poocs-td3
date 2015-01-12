#include "Pixel.hh"

Pixel::Pixel()
: N2(), _c(0) {}

Pixel::Pixel(const int x, const int y, const col c)
: N2(x, y), _c(c) {}

Pixel::Pixel(const N2& p, const col c)
: N2(p), _c(c) {}

col Pixel::couleur() const {
	return _c;
}

Pixel Pixel::operator+(const Pixel& c) const {
	return Pixel(_x+c._x, _y+c._y, _c+c._c);
}

Pixel Pixel::operator-(const Pixel& c) const {
	return Pixel(_x-c._x, _y-c._y, _c-c._c);
}

Pixel Pixel::operator/(const int c) const {
	return Pixel(_x/c, _y/c, _c/c);
}

std::ostream& operator<<(std::ostream& o, const Pixel& c) {
	return o << "("  << c._x
	         << ", " << c._y
	         << ", " << c._c << ")";
}
