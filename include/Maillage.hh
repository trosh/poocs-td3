#ifndef MAILLAGE_HH
#define MAILLAGE_HH

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <Triangle.hh>
#include <Tableau.hh>
#include <Cavite.hh>
#include <Image.hh>

class Maillage {
protected:
	Image *_image;
	Tableau<Triangle> _tri;
	bool *_in;
public:
	Maillage() {}
	Maillage(Image&);
	~Maillage();
	void sauvegarde(const char*) const;
	void ajoute(const int, const int);
};

#endif // MAILLAGE_HH
