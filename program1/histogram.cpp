#include "histogram.hpp"
#include <algorithm> 

Histogram::Histogram () 
{
	srednia_akt_ = false;
	odchylenie_akt_ = false;
}

void Histogram::dodaj (float x) 
{
	srednia_akt_ = false;
	odchylenie_akt_ = false;
	dane_.push_back(x);
}

size_t Histogram::rozmiar () const 
{
	return dane_.size();
}

float Histogram::srednia () const {
	if (srednia_akt_) {
		return srednia_;
	}
	float suma = 0;
	for (auto const &dana : dane_) 
		suma+=dana;
	srednia_ = suma/rozmiar();
	srednia_akt_ = true;
	return srednia_;
}

float Histogram::odchylenie () const 
{
	if (odchylenie_akt_) {
		return odchylenie_;
	}
	float sr = srednia();
	float suma = 0;
	for (auto const &dana : dane_) 
		suma+=pow(dana-sr,2);
	odchylenie_ = pow(suma/rozmiar(),0.5);
	odchylenie_akt_ = true;
	return odchylenie_;
}

float Histogram::max () const 
{
	return *std::max_element (dane_.begin(), dane_.end());
}

float Histogram::min () const 
{
	return *std::min_element (dane_.begin(), dane_.end());
}
