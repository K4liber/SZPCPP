#include "piec.hpp"

Piec::Piec (float temperatura) {
	temperatura_ = temperatura;
}

PiecDoswiadczalny::PiecDoswiadczalny (float temperatura): Piec(temperatura) {}
	
void Piec::dodajObserwatora (KontrolkaTemperatury* obs) {
	obserwatorzy_.push_back(obs);
}

void PiecDoswiadczalny::setTemp (float temperatura) {
	temperatura_ = temperatura;
	powiadom();
}

float PiecDoswiadczalny::getTemp () const {
	return temperatura_;
}

void Piec::powiadom () {
	for (int ii=0;ii<obserwatorzy_.size();ii++)
		obserwatorzy_[ii]->odswiez();
}
