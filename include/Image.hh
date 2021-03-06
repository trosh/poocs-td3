#ifndef IMAGE_HH
#define IMAGE_HH

#include <iostream>
#include <fstream>
#include <sstream>
#include <Pixel.hh>

class PGMException {
public:
	PGMException(const char * msg) : _msg(msg) { }
	const char * message() const { return _msg; }
private:
	const char * _msg;
};

class Image {
private:
	// sans cette signature le compilateur aurait inféré une implémentation
	// automatique de la construction par copie
	// on dévalue le sens de cette construction avec une signature fantôme
	Image(const Image&);
	Image & operator=(const Image&);
	unsigned _width;
	unsigned _height;
	unsigned _maxval;
	unsigned char * _data;
public:
	Image();
	Image(int, int);
	Image(const char*) throw (PGMException);
	~Image() { delete[] _data; }
	// ces methodes n'ont quasiment aucun cout, il est logique d'indiquer
	// au compilateur de ne pas leur affubler un overhead de fonction c
	inline unsigned width() const { return _width; }
	inline unsigned height() const { return _height; }
	inline unsigned maxval() const { return _maxval; }
	Pixel pixel(const N2&) const;
	Pixel pixel(const int, const int) const;
	unsigned numero(const N2&) const;
	// on prévoit qu'il faudra faire beaucoup de sommes de couleurs,
	// on s'authorise à overflow au cours de l'opération en renvoyant
	// un int plutôt qu'un char
	int operator()(const N2&) const;
	int operator()(int, int) const;
};

#endif // IMAGE_HH
