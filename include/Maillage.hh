#ifndef MAILLAGE_HH
#define MAILLAGE_HH

#include <Triangle.hh>
#include <Tableau.hh>

class Maillage {
protected:
	Image _image;
	Tableau<Triangle> _tri(1024);
public:
	Maillage() {}
	Maillage(const Image&);
	~Maillage() {}
	void sauvegarde(const char*) const;
	void ajoute(const int, const int);
}

#endif // MAILLAGE_HH
