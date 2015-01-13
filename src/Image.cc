#include <Image.hh>

Image::Image() : _width(0), _height(0), _data(NULL) {}

Image::Image(const char * filename) throw (PGMException)
: _width(0), _height(0),
  _maxval(0), _data(0) {
	std::ifstream file(filename, std::ios::binary);
	if (file.fail())
		throw PGMException("Cannot open file");
	// http://netpbm.sourceforge.net/doc/pgm.html
	std::string line;
	std::getline(file, line);
	bool is_binary = true;
	if      (line == "P5") is_binary = true;
	else if (line == "P2") is_binary = false;
	else throw PGMException("Bad PGM Header");
	std::getline(file, line);
	if (line[0] == '#') std::getline(file, line);
	std::istringstream is(line);
	is >> _width >> _height;
	const unsigned fullsize = _height * _width;
	file >> _maxval;
	if (_maxval > 255) throw PGMException("Too large max value");
	_data = new unsigned char[fullsize];
	if (is_binary)
		// reinterpret_cast permet de respecter le format d'entree de
		// file.read tout en utilisant un tableau statique
		file.read(reinterpret_cast<char*>(_data), fullsize);
	else
		for (unsigned i=0,v; i<fullsize; ++i) {
			// on passe par une variable intermédiaire car on utilise
			// la valeur deux fois et que c'est le resultat d'une
			// operation >> qu'on ne peut reutiliser que si on la stocke
			// v est de type unsigned int
			file >> v;
			if (v > _maxval) throw PGMException("Too big data");
			_data[i] = v;
		}
}

Pixel Image::pixel(const N2& X) const {
	if (X.x() < 0 || X.x() > _width
	 || X.y() < 0 || X.y() > _height)
		throw PGMException("Bad coords");
	return Pixel(X, _data[X.y()*_width+X.x()]);
}

Pixel Image::pixel(const int x, const int y) const {
	if (x < 0 || x > _width
	 || x < 0 || y > _height)
		throw PGMException("Bad coords");
	return Pixel(x, y, _data[y*_width+x]);
}

unsigned Image::numero(const N2& p) const {
	return p.y() * _width + p.x();
}

int Image::operator()(const N2& p) const {
	return _data[p.y()*_width+p.x()];
}

int Image::operator()(int y, int x) const {
	return _data[y*_width+x];
}
