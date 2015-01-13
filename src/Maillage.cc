#include <Maillage.hh>

Maillage::Maillage(Image& img)
: _image(&img) {
	_tri.reserve(1024);
	int h = img.height(),
	    w = img.width();
	_in = new bool[h*w];
	for (int i=0; i<h*w; i++)
		_in[i] = false;
	h--;
	w--;
	Triangle T1(img.pixel(0, 0),
	            img.pixel(w, 0),
	            img.pixel(0, h));
	Triangle T2(img.pixel(w, h),
	            img.pixel(0, h),
	            img.pixel(w, 0));
	_tri.ajoute(T1);
	_tri.ajoute(T2);
}

Maillage::~Maillage() {
	delete[] _in;
}

void Maillage::
sauvegarde(const char * filename) const {
	std::cout << "Saving '" << filename
	          << "' with " << _tri.taille() << " triangles\n";
	// VTK File formats : www.vtk.org/VTK/img/file-formats.pdf
	std::ofstream file(filename);
	file << "# vtk DataFile Version 3.0\n"
	     << "Maillage d'image\n"
	     << "ASCII\n"
	     << "DATASET UNSTRUCTURED_GRID\n"
	     << "\n"
	     << "POINTS ";
	std::map<int, int> coord_to_pos;
	std::ostringstream nodedata_oss;
	{
		std::ostringstream node_oss;
		for (int i=0; i<_tri.taille(); ++i) {
			const Triangle & tr = _tri[i];
			for (int j=0; j<3; ++j) {
				const Pixel & pixel = tr(j);
				std::pair<std::map<int,int>::iterator,bool> inserter
				= coord_to_pos.insert(
					std::make_pair<int,int>(
						_image->numero(pixel),
						coord_to_pos.size()));
				if (inserter.second) {
					node_oss << +pixel.x() << " "
					         << -pixel.y() << " 0\n";
					nodedata_oss << pixel.couleur() << "\n";
				}
			}
		}
		file << coord_to_pos.size() << " float\n"
		     << node_oss.str() << "\n";
	}
	file << "CELLS "
	     << _tri.taille() << " "
	     << 4*_tri.taille() << "\n";
	for (int i=0; i<_tri.taille(); ++i) {
		const Triangle & tr = _tri[i];
		file << "3 ";
		for (int j=0; j<3; ++j) {
			const Pixel & pixel = tr(j);
			file << coord_to_pos[_image->numero(pixel)] << " ";
		}
		file << "\n";
	}
	file << "\n"
	     << "CELL_TYPES " << _tri.taille() << "\n";
	for (int i=0; i<_tri.taille(); ++i)
		file << "5\n";
	file << "\n"
	     << "CELL_DATA " << _tri.taille() << "\n"
	     << "SCALARS cell_data int 1\n"
	     << "LOOKUP_TABLE default\n";
	for (int i=0; i<_tri.taille(); ++i) {
		const Triangle & tr = _tri[i];
		file << tr.barycentre().couleur() << "\n";
	}
	file << "\n"
	     << "POINT_DATA " << coord_to_pos.size() << "\n"
	     << "SCALARS node_data int 1\n"
	     << "LOOKUP_TABLE default\n"
	     << nodedata_oss.str();
}

int abs(int n) {
	if (n<0) return -n;
	return n;
}

void Maillage::ajoute(const int n, const int precision) {
	for (int i=0; i<n; i++) {
		Pixel p;
		int max_ecart = 0;
		bool flag = true;
		for (int t=0; t<_tri.taille(); t++) {
			const Pixel& cp = _tri[t].barycentre();
			if (_in[cp.y()*_image->width()+cp.x()]) continue;
			flag = false;
			int ecart = abs(cp.couleur() - (*_image)(cp));
			if (ecart > max_ecart) {
				p = cp;
				max_ecart = ecart;
			}
		}
		if (i%2000 == 0)
			std::cout << i << " "
			          << max_ecart << " " << std::endl;
		if (max_ecart <= precision) {
			std::cout << "max_ecart <= precision :)\n";
			return;
		}
		p = Pixel(p, (*_image)(p));
		Cavite cavite(_tri, p);
		const Tableau<int>& AT = cavite.AnciensTriangles();
		// ON EST SÛR QUE AT[I] < AT[I+1]
		for (int k=AT.taille()-1; k>=0; k--)
			_tri.supprime(AT[k]);
		const Tableau<Pixel>& PDC = cavite.pixelsDuContour();
		for (int k=0; k<PDC.taille(); k++) {
			Triangle Tk(PDC[k], PDC[(k+1)%PDC.taille()], p);
			_tri.ajoute(Tk);
			_in[p.y()*_image->width()+p.x()] = true;
		}
	}
	std::cout << "reached n\n";
}
