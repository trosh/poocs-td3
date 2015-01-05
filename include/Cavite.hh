#ifndef CAVITE_HH
#define CAVITE_HH

#include <Pixel.hh>
#include <map>
#include <cmath>

class Cavite {
private:
	Tableau<int> m_numeros_anciens_triangles;
	Tableau<Pixel> m_pixels_du_contour;
public:
	Cavite(const Tableau<Triangle>& triangles,
	       const Pixel& nouveau_point) {
		typedef std::map<double, Pixel> PixelOrdonnes;
		PixelOrdonnes pixel_ordonnes;
		for (int i=0; i<triangles.taille(); ++i) {
			const Triangle& triangle = triangles[i];
			if (triangle.cercleCirconscritContient(nouveau_point)) {
				m_numeros_anciens_triangles.ajoute(i);
				for (int j=0; j<3; ++j) {
					const Pixel& p = triangle(j);
					const double& angle = atan2(p.y()-nouveau_point.y(),
					                            p.x()-nouveau_point.x());
					pixel_ordonnes[angle] = p;
				}
			}
		}
		m_pixels_du_contour.reserve(pixel_ordonnes.size());
		for (PixelOrdonnes::const_iterator i=pixel_ordonnes.begin();
		     i!=pixel_ordonnes.end(); ++i) {
			m_pixels_du_contour.ajoute(i->second);
		}
	}
	~Cavite() {}
public:
	const Tableau<int>& numerosAnciensTriangles() const {
		return m_numeros_anciens_triangles;
	}
	const Tableau<Pixel>& pixelsDuContour() const {
		return m_pixels_du_contour;
	}
};

#endif // CAVITE_HH
