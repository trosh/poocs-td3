#include "N2.hh"

N2::N2()
: _x(0), _y(0) { }

N2::N2(int x, int y)
: _x(x), _y(y) { }

N2::N2(const N2& p)
: _x(p._x), _y(p._y) { }

int N2::x() const {
	return _x;
}

int N2::y() const {
	return _y;
}

N2 N2::operator+(const N2 & c) const {
	return N2(_x+c._x, _y+c._y);
}

N2 N2::operator-(const N2 & c) const {
	return N2(_x-c._x, _y-c._y);
}

N2 N2::operator/(int c) const {
	if (!c) throw DivideByZero;
	return N2(_x/c, _y/c);
}

bool N2::operator==(const N2& that) const {
	return _x == that._x and _y == that._y;
}

std::ostream& operator<<(std::ostream& o, const N2& c) {
	return o << "(" << c._x << ", " << c._y << ")";
}
