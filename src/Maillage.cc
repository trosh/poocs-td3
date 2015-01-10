#include <Maillage.hh>
#include <iostream>
#include <fstream>

Maillage::Maillage(const Image& img) _image(img) {
	int h = img.nbLignes()-1,
	    w = img.nbColonnes()-1;
	Triangle T1(img.pixel(0, 0),
	            img.pixel(0, h),
	            img.pixel(w, 0));
	Triangle T2(img.pixel(w, h),
	            img.pixel(w, 0),
	            img.pixel(0, h));
	_tri.ajoute(T1);
	_tri.ajoute(T2);
}

void Maillage::
sauvegarde(const char * filename) const {
	std::cout << "Saving '" << filename
	          << "' with " << m_triangles.taille() << " triangles\n";
	// VTK File formats : www.vtk.org/VTK/img/file-formats.pdf
	std::ofstream file(filename);
	file << "# vtk DataFile Version 3.0\n"
	     << "Maillage d'image\n"
	     << "ASCII\n"
	     << "DATASET UNSTRUCTURED_GRID\n"
	     << "\n"
	     << "POINTS ";
	std::map<int,int> coord_to_pos;
	std::ostringstream nodedata_oss;
	{
		std::ostringstream node_oss;
		for (int i=0; i<m_triangles.taille(); ++i) {
			const Triangle & tr = m_triangles[i];
			for (int j=0; j<3; ++j) {
				const Pixel & pixel = tr(j);
				std::pair<std::map<int,int>::iterator,bool> inserter
				= coord_to_pos.insert(
					std::make_pair<int,int>(
						m_image.numero(pixel),
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
	     << m_triangles.taille() << " "
	     << 4*m_triangles.taille() << "\n";
	for (int i=0; i<m_triangles.taille(); ++i) {
		const Triangle & tr = m_triangles[i];
		file << "3 ";
		for (int j=0; j<3; ++j) {
			const Pixel & pixel = tr(j);
			file << coord_to_pos[m_image.numero(pixel)] << " ";
		}
		file << "\n";
	}
	file << "\n"
	     << "CELL_TYPES " << m_triangles.taille() << "\n";
	for (int i=0; i<m_triangles.taille(); ++i)
		file << "5\n";
	file << "\n"
	     << "CELL_DATA " << m_triangles.taille() << "\n"
	     << "SCALARS cell_data int 1\n"
	     << "LOOKUP_TABLE default\n";
	for (int i=0; i<m_triangles.taille(); ++i) {
		const Triangle & tr = m_triangles[i];
		file << tr.barycentre().couleur() << "\n";
	}
	file << "\n"
	     << "POINT_DATA " << coord_to_pos.size() << "\n"
	     << "SCALARS node_data int 1\n"
	     << "LOOKUP_TABLE default\n"
	     << nodedata_oss.str();
}

int abs(int n) {
	if (n>=0) return n;
	return -n;
}

void Maillage::ajoute(const int n, const int precision) {
	int t = 0;
	int completed = 0;
	for (int i=0; i<n; i++) {
		if (t >= _tri.taille())
			t = 0;
		Pixel& p = _tri[t].barycentre();
		if (abs(p.col() - img.pixel(p).col()) <= precision) {
			t++;
			completed++;
			if (completed == _tri.taille()) return;
			continue;
		}
		completed = 0;
		Tableau<Pixel> cavite(32);
		for (int j=0; j!=_tri.taille(); ) {
			Triangle& Tj = _tri[j];
			// FIND OUT IF CIRCONSCRIT
			if (!Tj.cercleCirconscritContient(p)) {
				j++;
				continue;
			}
			// ADD TO CAVITE
			bool p0in = p1in = p2in = false;
			for (k=0; k<cavite.taille(); k++) {
				Pixel& Pk = cavite[k];
				if (Pk == Tj(0)) p0in = true;
				if (Pk == Tj(1)) p1in = true;
				if (Pk == Tj(2)) p2in = true;
			}
			if (not p0in) cavite.ajoute(Tj(0));
			if (not p1in) cavite.ajoute(Tj(1));
			if (not p2in) cavite.ajoute(Tj(2));
			_tri.supprime(j);
			Tj = NULL;
			// SORT BY ATAN2
			Tableau<float> angles(cavite.taille());
			for (k=0; k<cavite.taille(); k++) {
				Pixel& Pk = cavite[k];
				angles.ajoute(atan2(Pk.x()-p.x(), Pk.y()-p.y()));
			}
			for (k=0; k<angles.taille()-1; k++) {
				float& Fk = angle[k];
				for (l=k+1; l<angles.taille(); l++) {
					float& Fl = angles[l];
					if (Fl < Fk) {
						Pixel tempP = cavite[l];
						cavite[l] = cavite[k];
						cavite[k] = tempP;
						float tempF = Fl;
						Fl = Fk;
						Fk = tempF;
					}
				}
			}
			for (k=0; k<cavite.taille()-1; k++) {
				Triangle Tk(cavite[k], cavite[k+1], p);
				_tri.ajoute(Tk);
			}
		t++;
	}
}
