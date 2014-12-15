#ifndef N2_HH
#define N2_HH

#include <iostream>

enum {
	DivideByZero
};

class N2 {
protected:
	int _x;
	int _y;
public:
	N2();
	N2(int x, int y);
	N2 operator+(const N2 & c) const;
	N2 operator-(const N2 & c) const;
	N2 operator/(const double & c) const;
}

#endif // N2_HH
