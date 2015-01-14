#include <Triangle.hh>

Triangle::Triangle()
: _0(Pixel()), _1(Pixel()), _2(Pixel()) {}

Triangle::
Triangle(const Pixel& p0, const Pixel& p1, const Pixel& p2)
: _0(p0), _1(p1), _2(p2) {}

const Pixel Triangle::barycentre() const {
	return Pixel((_0+_1+_2)/3,
	             (_0.couleur()
	             +_1.couleur()
	             +_2.couleur())/3);
}

const Pixel& Triangle::
operator()(const int n) const {
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

long long int SQ(int n) {
	return n*n;
}

bool Triangle::
cercleCirconscritContient(const N2& d) const {
	long long int D,
		x0 = _0.x(), y0 = _0.y(),
		x1 = _1.x(), y1 = _1.y(),
		x2 = _2.x(), y2 = _2.y(),
		xd =  d.x(), yd =  d.y(),
		A2 = SQ(x0) - SQ(xd) + SQ(y0) - SQ(yd),
		B2 = SQ(x1) - SQ(xd) + SQ(y1) - SQ(yd),
		C2 = SQ(x2) - SQ(xd) + SQ(y2) - SQ(yd);
	D = (x0 - xd)
	  * ( (y1 - yd) * C2
	    - (y2 - yd) * B2 );
	D-= (x1 - xd)
	  * ( (y0 - yd) * C2
	    - (y2 - yd) * A2 );
	D+= (x2 - xd)
	  * ( (y0 - yd) * B2
	    - (y1 - yd) * A2 );
	return D > 0;
}
