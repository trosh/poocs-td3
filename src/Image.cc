#include <Image.hh>

Pixel& Image::pixel(const N2& X) const {
	for (int i=0; i<taille; i++)
		if (_cont[i].x() == X.x()
		 && _cont[i].y() == X.y())
			return _cont[i];
	throw badCoord;
}

Pixel& Image::pixel(const int& x, const int& y) const {
	for (int i=0; i<taille; i++)
		if (_cont[i].x() == x()
		 && _cont[i].y() == y())
			return _cont[i];
	throw badCoord;
}

int Image::nbLignes() const {
	return _w;
}

int Image::nbColonnes() const {
	return _h;
}
