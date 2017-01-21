#include "macierz.hpp"
#include <vector>
#include <cstring>
#include <utility> 

Macierz::Macierz (std::istream &is) {
	std::vector<std::vector<int>> wersy;
	char call[100000];
	//Wczytywanie danych ze standardowego wejscia do blng_
	while (is.getline(call,100000)) {
		std::vector<int> wers;
		char* chars_array = strtok(call, "\t");
		while (chars_array)
		{
			wers.push_back(atoi(chars_array));
			chars_array = strtok(NULL, "\t");
		}
		wersy.push_back(wers);
	}
	
	n_ = wersy.size();
	m_ = wersy[0].size();
	mac_ = new int*[n_];
	for ( int ii=0;ii<n_;ii++ ) {
		mac_[ii] = new int[m_];
	}
	for ( int ii=0;ii<n_;ii++ ) {
		for ( int jj=0;jj<m_;jj++ ) 
			mac_[ii][jj] = wersy[ii][jj];
	}
}

Macierz::~Macierz () {
	for ( int ii=0;ii<n_;ii++ ) {
		delete[] mac_[ii];
	}
	delete[] mac_;
}

Macierz::Macierz (int n, int m) {
	mac_ = new int*[n];
	for ( int ii=0;ii<n;ii++ ) {
		mac_[ii] = new int[m];
	}
}

int Macierz::element (int i, int j) const{
	return mac_[i][j];
}

int &Macierz::getElement (int i, int j) {
	return mac_[i][j];
}

RozmiarMacierzy Macierz::rozmiar () const{
	RozmiarMacierzy r = std::make_pair(n_,m_);
	return r;
}

std::ostream &operator<< (std::ostream &os, const Macierz &m) {
	return os;
}
