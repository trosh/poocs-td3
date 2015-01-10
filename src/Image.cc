#include <Image.hh>

Image::Image() : _w(0), _h(0), _cont(NULL) {}

Image::Image(int w, int h)
: _w(w), _h(h) {
	_cont = new Pixel[w*h];
}

Image::Image(const PGMImage& i)
: _w(i.width()),
  _h(i.height()) {
	_cont = new Pixel[w*h];
	
}

Image::~Image() {
	delete[] Pixel;
}

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
