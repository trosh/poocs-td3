#include <iostream> // cout
#include <sstream>  // istringstream
#include <fstream>  // ifstream
#include <string>   // string
#include <iomanip>  // setw

class PGMException {
public:
	PGMException(const char * msg) : m_msg(msg) { }
	const char * message() const { return m_msg; }
private:
	const char * m_msg;
};

class Image {
private:
	// sans cette signature le compilateur aurait inféré une implémentation
	// automatique de la construction par copie
	// on dévalue le sens de cette construction avec une signature fantôme
	Image(const Image&);
	Image & operator=(const PGMImage&);
	unsigned m_width;
	unsigned m_height;
	unsigned m_maxval;
	unsigned char * m_data;
public:
	Image();
	Image(int, int);
	Image(const PGMImage&);
	~Image() { delete[] _cont; }
	// ces methodes n'ont quasiment aucun cout, il est logique d'indiquer
	// au compilateur de ne pas leur affubler un overhead de fonction c
	inline unsigned width() const { return _w; }
	inline unsigned height() const { return _h; }
	// on prévoit qu'il faudra faire beaucoup de sommes de couleurs,
	// on s'authorise à overflow au cours de l'opération en renvoyant
	// un int plutôt qu'un char
	inline unsigned operator()(int i, int j) const {
		return _cont[i*m_width+j];
	}
};

class PGMImage {
public:
	Image toImage(const char * filename) throw (PGMException);
}

PGMImage::PGMImage(const char * filename) throw (PGMException)
: m_width(0), m_height(0),
  m_maxval(0), m_data(0) {
	std::ifstream file(filename, std::ios::binary);
	if (file.fail())
		throw PGMException("Cannot open file");
	// http://netpbm.sourceforge.net/doc/pgm.html
	std::string line;
	std::getline(file, line);
	bool is_binary = true;
	if (line == "P5")
		is_binary = true;
	else if (line == "P2" )
		is_binary = false;
	else
		throw PGMException("Bad PGM Header");
	std::getline(file, line);
	if (line[0] == '#')
		std::getline(file, line);
	std::istringstream is(line);
	is >> m_width >> m_height;
	const unsigned fullsize = m_height*m_width;
	file >> m_maxval;
	if (m_maxval > 255)
		throw PGMException("Too large max value");
	m_data = new unsigned char[fullsize];
	if (is_binary)
		// reinterpret_cast permet de respecter le format d'entree de file.read
		// tout en utilisant un tableau statique
		file.read(reinterpret_cast<char*>(m_data), fullsize);
	else
		for (unsigned i=0,v; i<fullsize; ++i) {
			// on passe par une variable intermédiaire car on utilise
			// la valeur deux fois et que c'est le resultat d'une operation
			// >> qu'on ne peut reutiliser que si on la stocke
			// v est de type unsigned int
			file >> v;
			if (v > m_maxval) throw PGMException("Too big data");
			m_data[i] = v;
		}
}

int main() {
	PGMImage img("Image/a.pgm");
	const int statsize = 16;
	int stats[statsize];
	for(int i=0;i<statsize;++i) 
		stats[i] = 0;
	for(unsigned i=0; i<img.height(); ++i)
		for(unsigned j=0; j<img.width(); ++j)
			stats[statsize*img(i,j)/256]++;
	std::cout << "Image " << img.width()
	          << " x " << img.height()
	          << " by " << (img.maxval()+1) << " values\n";
	std::cout << "Stats:\n";
	const unsigned fullsize = img.height()*img.width();
	for(int i=0;i<statsize;++i) {
		// si on met la multiplication par 100  à la fin, on obtient 0
		// parce que stats est un tableau d'entiers et que pour tout i,
		// stats[i] < fullsize
		const unsigned linesize = 100*stats[i]/fullsize;
		std::cout << std::setw(3) << linesize << "% : ";
		for(unsigned j=0;j<linesize;++j) std::cout << "*";
		std::cout << "\n";
	}
}
