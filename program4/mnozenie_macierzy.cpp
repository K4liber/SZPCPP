#include "mnozenie_macierzy.hpp"
#include <boost/thread.hpp>
#include <utility> 

KontrolerMnozenia::KontrolerMnozenia
	(const Macierz &m1, const Macierz &m2, Macierz &m3): 
		m1_(m1), m2_(m2), m3_(m3) {
	wiersz = 0;
	kolumna = 0;
}

boost::optional <Polozenie> KontrolerMnozenia::coMamLiczyc () {
	//blokada_.lock();
	Polozenie pol = std::make_pair (wiersz, kolumna);
	RozmiarMacierzy rozmiar = this->m3_.rozmiar();
	if( wiersz < std::get<0>(rozmiar) ) {
		if( kolumna+1 == std::get<1>(rozmiar) ) {
			kolumna = 0;
			wiersz++;
		} else {
			kolumna++;
		}
		return pol;
	}
	//blokada_.unlock();
}

MnozycielMacierzy::MnozycielMacierzy (KontrolerMnozenia &km): km_(km) {
	m1_ = &km.czynnik1();
	m2_ = &km.czynnik2();
	m3_ = &km.wynik();
}

void MnozycielMacierzy::operator() () {
	while ( boost::optional <Polozenie> opol = km_.coMamLiczyc() ) {
		Polozenie pol = *opol;
		int suma = 0;
		RozmiarMacierzy rozmiar = m1_->rozmiar();
		for ( int ii=0;ii<std::get<1>(rozmiar);ii++ ) {
			suma+=(this->m1_->element(std::get<0>(pol),ii))*
					(this->m2_->element(ii, std::get<1>(pol)));
		}
		m3_->getElement(std::get<0>(pol),std::get<1>(pol)) = suma;
		std::cout<<"("<<std::get<0>(pol)<<", "<<std::get<1>(pol)<<"): "<<suma<<std::endl;
	}
}

void mnozenie_macierzy 
	(const Macierz &m1, const Macierz &m2, Macierz &m3, int p) {
	
	KontrolerMnozenia km(m1, m2, m3);
	boost::thread_group watki;
	std::vector <MnozycielMacierzy*> mnozyciele;
	
	for (int i = 0; i < p; ++i) {// przydziela zakresy poszczególnym obiektom
		mnozyciele.push_back (new MnozycielMacierzy(km));
	}

	for (int i = 0; i < p; ++i) // tworzy wątki
		watki.create_thread (std::ref (*(mnozyciele [i])));
	watki.join_all (); // czeka na zakończenie wszystkich obliczeń
	
}
