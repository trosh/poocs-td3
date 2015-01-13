#ifndef CAVITE_HH
#define CAVITE_HH

#include <Tableau.hh>
#include <Triangle.hh> // -> Pixel -> N2
#include <map>
#include <cmath>

typedef std::map<double, Pixel> PixelOrdonnes;

class Cavite {
private:
	Tableau<int> _anciens_triangles;
	Tableau<Pixel> _pixels_du_contour;
public:
	Cavite(const Tableau<Triangle>&, const Pixel&);
	~Cavite() {}
	const Tableau<int>& AnciensTriangles() const;
	const Tableau<Pixel>& pixelsDuContour() const;
};

#endif // CAVITE_HH
