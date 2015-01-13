#include <Cavite.hh>

Cavite::Cavite(const Tableau<Triangle>& triangles,
               const Pixel& nouveau_point) {
	PixelOrdonnes pixel_ordonnes;
	for (int i=0; i<triangles.taille(); ++i) {
		const Triangle& triangle = triangles[i];
		if (triangle.cercleCirconscritContient(nouveau_point)) {
			_anciens_triangles.ajoute(i);
			for (int j=0; j<3; ++j) {
				const Pixel& p = triangle(j);
				const double& angle = atan2(p.y()-nouveau_point.y(),
				                            p.x()-nouveau_point.x());
				pixel_ordonnes[angle] = p;
			}
		}
	}
	_pixels_du_contour.reserve(pixel_ordonnes.size());
	for (PixelOrdonnes::const_iterator i=pixel_ordonnes.begin();
	     i!=pixel_ordonnes.end(); ++i) {
		_pixels_du_contour.ajoute(i->second);
	}
}

const Tableau<int>& Cavite::AnciensTriangles() const {
	return _anciens_triangles;
}

const Tableau<Pixel>& Cavite::pixelsDuContour() const {
	return _pixels_du_contour;
}
