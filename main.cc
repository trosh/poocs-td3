#include <iostream>
#include "Tableau.hh"
#include "N2.hh"

typedef struct { double r, i; } C;

std::ostream& operator<<(std::ostream& o, const C& c) {
	o << c.r;
	if (c.i > 0)
		o << "+";
	return o << c.i << "i";
}

int main() {
	using namespace std;
	Tableau<C> tab(5);
	for (int i=0; i<5; i++) {
		C c = {1.4+i, 1.4-i};
		tab.ajoute(c);
	}
	std::cout << tab;
	Tableau<C> tab2 = tab;
	tab.~Tableau<C>();
	std::cout << tab2;
	N2 p(2, 4), q(4, 2);
	std::cout << p+q << std::endl;
	return 0;
}
