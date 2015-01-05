#include "N2.hh"

N2::N2()
: _x(0), _y(0) { }

N2::N2(int x, int y)
: _x(x),
  _y(y) { }

inline int N2::x() const {
	return _x;
}

inline int N2::y() const {
	return _y;
}

inline N2 N2::operator+(const N2 & c) const {
	return N2(_x+c._x, _y+c._y);
}

inline N2 N2::operator-(const N2 & c) const {
	return N2(_x-c._x, _y-c._y);
}

N2 N2::operator/(int c) const {
	if (!c) throw DivideByZero;
	return N2(_x/c, _y/c);
}

inline bool N2::operator==(const N2& that) const {
	return this.x == that.x and this.y == that.y;
}

inline std::ostream& operator<<(std::ostream& o, const N2& c) {
	return o << "(" << c._x << ", " << c._y << ")";
}
