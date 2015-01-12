#ifndef TRIANGLE_HH
#define TRIANGLE_HH

#include <Pixel.hh>

enum TriangleError {
	BadValue
};

class Triangle {
protected:
	Pixel _0;
	Pixel _1;
	Pixel _2;
public:
	Triangle();
	Triangle(const Pixel&, const Pixel&, const Pixel&);
	~Triangle() {}
	const Pixel barycentre() const;
	const Pixel& operator()(const int) const;
	bool cercleCirconscritContient(const N2&) const;
};

#endif // TRIANGLE_HH
