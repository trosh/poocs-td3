#include <iostream> // cout
#include <sstream>  // istringstream
#include <fstream>  // ifstream
#include <string>   // string
#include <iomanip>  // setw

int main() {
	Image img("Image/a.pgm");
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
