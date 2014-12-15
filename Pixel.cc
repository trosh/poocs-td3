#include "Pixel.hh"

Pixel::Pixel()
: N2(), _c(0) {}

Pixel::Pixel(int x, int y, col c)
: N2(x, y), _c(c) {
	if (c<0 || c>255)
		throw BadValue;
}

Pixel::Pixel(const N2& p, col c)
: N2(p.x(), p.y()),
  _c(c) {
	if (c<0 || c>255)
		throw BadValue;
}

col Pixel::couleur(int x, int y) const {
	return _c;
}

Pixel Pixel::operator+(const Pixel& c) const {
	return Pixel(_x+c._x, _y+c._y, _c+c._c);
}

Pixel Pixel::operator-(const Pixel& c) const {
	return Pixel(_x-c._x, _y-c._y, _c-c._c);
}

Pixel Pixel::operator/(int c) const {
	return Pixel(_x/c, _y/c, _c/c);
}

std::ostream& operator<<(std::ostream& o, const Pixel& c) {
	return o << "("  << c._x
	         << ", " << c._y
	         << ", " << c._c << ")";
}
