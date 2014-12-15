#ifndef N2_HH
#define N2_HH

#include <iostream>

enum Error {
	DivideByZero
};

class N2 {
protected:
	int _x;
	int _y;
public:
	N2();
	N2(int x, int y);
	int x();
	int y();
	N2 operator+(const N2 & c) const;
	N2 operator-(const N2 & c) const;
	N2 operator/(int c) const;
friend std::ostream& operator<<(std::ostream& o, const N2& c);
};

#endif // N2_HH
