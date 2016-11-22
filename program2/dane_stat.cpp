#include "dane_stat.hpp"

DaneStat::DaneStat (const std::string &nazwa) {
	nazwa_ = nazwa;
}

const std::string& DaneStat::nazwa() const {
	return nazwa_;
}

const std::vector <float>& DaneStatProxy::dane () const {
	return dane_->dane();
}

DaneStatProxy::DaneStatProxy(const std::string &nazwa) : DaneStat(nazwa) {
	
}

DaneStatReal::DaneStatReal (const std::string &nazwa) : DaneStat(nazwa) {
	
}

const std::vector <float>& DaneStatReal::dane () const {
	return vectorData;
}

std::vector <float> & DaneStat::wczytajDane() {
	
}

std::vector <float> & DaneStatProxy::wczytajDane() {
	if (!dane_) {
		dane_ = new DaneStatReal(nazwa_);
	} 
	return dane_->wczytajDane();
}

std::vector <float> & DaneStatReal::wczytajDane() {
	if ( vectorData.empty() ) {
		char charLine[20];
		std::string line;
		std::string path = "files/" + nazwa_;
		std::ifstream plik;
		plik.open(path.c_str(), std::ifstream::in);
		if ( plik.good() ) {
			while ( std::getline(plik, line) ) {
				vectorData.push_back(atof(line.c_str()));
			}
		}
	}
	return vectorData;
}
