#include <Triangle.hh>

Triangle::Triangle()
: _0(Pixel()), _1(Pixel()), _2(Pixel()) {}

Triangle::
Triangle(const Pixel& p0, const Pixel& p1, const Pixel& p2)
: _0(p0), _1(p1), _2(p2) {}

const Pixel Triangle::barycentre() const {
	return Pixel((_0+_1+_2)/3,
	             (_0.col+_1.col+_2.col)/3);
}

const Pixel& Triangle::
operator()(const int& n) const {
	switch (n) {
	case 0 : {
		return _0;
		break;
	} case 1 : {
		return _1;
		break;
	} case 2 : {
		return _2;
		break;
	}
	}
	throw BadValue;
}

inline int SQ(int n) {
	return n*n;
}

bool Triangle::
cercleCirconscritContient(const N2& d) const {
	long long int D,
		A2 = SQ(_0.x()) - SQ(d.x()) + SQ(_0.y()) - SQ(d.y()),
		B2 = SQ(_1.x()) - SQ(d.x()) + SQ(_1.y()) - SQ(d.y()),
		C2 = SQ(_2.x()) - SQ(d.x()) + SQ(_2.y()) - SQ(d.y());
	D = (_0.x() - d.x())
	  * ( (_1.y() - d.y()) * C2
	    - (_2.y() - d.y()) * B2 );
	D-= (_1.x() - d.x())
	  * ( (_0.y() - d.y()) * C2
	    - (_2.y() - d.y()) * A2 );
	D+= (_2.x() - d.x())
	  * ( (_0.y() - d.y()) * B2
	    - (_1.y() - d.y()) * A2 );
	return D > 0;
}
