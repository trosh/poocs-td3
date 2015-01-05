#ifndef TABLEAU_HH
#define TABLEAU_HH

#include <iostream>
#include <cassert>

template<typename T>
class Tableau;

template<typename T>
std::ostream& operator<<(std::ostream&, const Tableau<T>&);

template<typename T>
class Tableau {
protected:
	int _taille;
	int _capacite;
	T* _contenu;
public:
	// constructeurs
	Tableau();
	Tableau(int); // capacite
	Tableau(const Tableau<T>&);
	// destructeur
	~Tableau();
	// methodes const
	int taille() const;
	int capacite() const;
	T& operator[](int) const;
	// methodes
	void retaille(int);
	void reserve(int);
	void ajoute(const T&);
	void supprime(int);
	const Tableau<T>& operator=(const Tableau<T>&);
};

template<typename T>
Tableau<T>::
Tableau()
: _taille(0), _capacite(4) {
	_contenu = new T[_capacite];
}

template<typename T>
Tableau<T>::
Tableau(int capacite)
: _taille(0), _capacite(capacite) {
	assert(capacite >= 0);
	_contenu = new T[_capacite];
}

template<typename T>
Tableau<T>::
Tableau(const Tableau<T>& tab)
: _taille(0), _capacite(0), _contenu(NULL) {
	operator=(tab);
}

template<typename T>
Tableau<T>::
~Tableau() {
	delete[] _contenu;
}

template<typename T>
int
Tableau<T>::
taille() const {
	return _taille;
}

template<typename T>
int
Tableau<T>::
capacite() const {
	return _capacite;
}

// realloc
template<typename T>
void
Tableau<T>::
reserve(int capacite) {
	if (capacite <= _capacite) return;
	T* new_contenu = new T[capacite];
	for (int i=0; i<_taille; i++)
		new_contenu[i] = _contenu[i];
	delete[] _contenu;
	_contenu = new_contenu;
	_capacite = capacite;
}

template<typename T>
void
Tableau<T>::
retaille(int taille) {
	assert(taille >= 0);
	if (taille > _capacite)
		reserve(2*_capacite);
	_taille = taille;
}

template<typename T>
void
Tableau<T>::
ajoute(const T& elem) {
	retaille(_taille+1); // _taille++, realloc si necessaire
	_contenu[_taille-1] = elem;
}

template<typename T>
void
Tableau<T>::
supprime(int key) {
	assert(key >= 0);
	assert(_taille > 0);
	if (key != _taille-1) {
		_contenu[key] = _contenu[_taille-1];
		_contenu[_taille-1] = T();
	}
	retaille(_taille-1);
}

template<typename T>
T&
Tableau<T>::
operator[](int key) const {
	assert(key>=0 && key<_taille);
	return _contenu[key];
}

template<typename T>
const Tableau<T>&
Tableau<T>::
operator=(const Tableau<T>& tab) {
	if (tab._capacite != _capacite) {
		delete[] _contenu;
		_capacite = tab._capacite;
		_contenu = new T[_capacite];
	}
	_taille = tab._taille;
	for (int i=0; i<_taille; i++)
		_contenu[i] = tab._contenu[i];
	return tab;
}

template<typename T>
std::ostream&
operator<<(std::ostream& o, const Tableau<T>& tab) {
	o << "[";
	for (int i=0; i<tab.taille()-1; i++)
		o << tab[i] << ", ";
	if (tab.taille() > 0)
		o << tab[tab.taille()-1];
	o << "]";
	return o;
}

#endif // TABLEAU_HH
