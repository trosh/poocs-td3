#include <iostream>
#include "Tableau.hh"
#include "N2.hh"
#include "Pixel.hh"

typedef struct { double r, i; } C;

std::ostream& operator<<(std::ostream& o, const C& c) {
	o << c.r;
	if (c.i > 0)
		o << "+";
	return o << c.i << "i";
}

using std::cout;
using std::endl;

int main() {
	using namespace std;
	// TABLEAU
	cout << "TABLEAU<C> (COMPLEXES)" << endl;
	Tableau<C> tab(5);
	for (int i=0; i<5; i++) {
		C c = {1.4+i, 1.4-i};
		tab.ajoute(c);
	}
	cout << tab << endl;
	Tableau<C> tab2 = tab;
	cout << "TAB2(TAB1)" << endl;
	tab.~Tableau<C>();
	cout << "TAB1.~TABLEAU<C>()" << endl;
	cout << tab2 << endl;
	// N2
	cout << endl << "N2 (SOMME)" << endl;
	N2 p(2, 4), q(4, 2);
	Tableau<N2> tabc(3);
	tabc.ajoute(p);
	tabc.ajoute(q);
	tabc.ajoute(p+q);
	cout << tabc << endl;
	// PIXELS
	cout << endl << "PIXEL (BARYCENTRE)" << endl;
	Pixel P1(2, 2, 10), P2(4, 5, 20);
	Tableau<Pixel> tabp(3);
	tabp.ajoute(P1);
	tabp.ajoute(P2);
	tabp.ajoute((P1+P2)/2);
	cout << tabp << endl;
	return 0;
}
