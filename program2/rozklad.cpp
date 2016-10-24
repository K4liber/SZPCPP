#include "rozklad.hpp"

Rozklad::Rozklad (const std::vector <float> &dane) : dane_(dane){}
RozkladGaussa::RozkladGaussa (const std::vector <float> &dane) : Rozklad (dane) {}
RozkladPoissona::RozkladPoissona (const std::vector <float> &dane) : Rozklad (dane) {}
RozkladLorentza::RozkladLorentza (const std::vector <float> &dane) : Rozklad (dane) {}
// Statyczny kreator wybranej klasy (to naprawdę jest takie proste!)
Rozklad *RozkladGaussa::kreator (const std::vector <float> &dane)
{
	return new RozkladGaussa (dane);
}
Rozklad *RozkladPoissona::kreator (const std::vector <float> &dane)
{
	return new RozkladPoissona (dane);
}
Rozklad *RozkladLorentza::kreator (const std::vector <float> &dane)
{
	return new RozkladLorentza (dane);
}

std::map <unsigned, KreatorRozkladu> FabrykaRozkladow::rozklady;
std::map <unsigned, std::string> FabrykaRozkladow::nazwy;
int FabrykaRozkladow::index = 1;
std::string FabrykaRozkladow::nazwa (unsigned id) { return nazwy[id]; }

// Statyczna metoda wołająca (choć trudno to zobaczyć) kreator typu o podanym id
Rozklad *FabrykaRozkladow::utworz (unsigned typ, const std::vector <float> &dane)
{
	return rozklady [typ] (dane);
}

void FabrykaRozkladow::rejestruj (KreatorRozkladu kreator, const std::string &nazwa)
{
	rozklady.insert( std::pair<unsigned,KreatorRozkladu>( index, kreator) );
	nazwy.insert( std::pair<unsigned,std::string>( index, nazwa) );
	index++;
}

unsigned FabrykaRozkladow::ilosc () {
	return rozklady.size();
}

ParametryRozkladu RozkladLorentza::oblicz() const{
	float suma = 0;
	int ilosc = 0;
	float odchylenie = 0;
	float srednia = 0;
	for ( int ii=0;ii<dane_.size();ii++ ) {
		suma+=dane_[ii];
		ilosc++;
	}
	srednia = suma/ilosc;
	for ( int ii=0;ii<dane_.size();ii++ ) {
		odchylenie += pow(dane_[ii] - srednia,2);
	}
	odchylenie/=ilosc;
	odchylenie = pow(odchylenie, 0.5);
	
	ParametryRozkladu parametry;
	parametry.insert( std::pair<std::string,float>("srednia", srednia) );
	parametry.insert( std::pair<std::string,float>("odchylenie", odchylenie) );
	
	return parametry;
}

ParametryRozkladu RozkladPoissona::oblicz() const{
	float suma = 0;
	int ilosc = 0;
	float odchylenie = 0;
	float srednia = 0;
	for ( int ii=0;ii<dane_.size();ii++ ) {
		suma+=dane_[ii];
		ilosc++;
	}
	srednia = suma/ilosc;
	for ( int ii=0;ii<dane_.size();ii++ ) {
		odchylenie += pow(dane_[ii] - srednia,2);
	}
	odchylenie/=ilosc;
	odchylenie = pow(odchylenie, 0.5);
	
	ParametryRozkladu parametry;
	parametry.insert( std::pair<std::string,float>("srednia", srednia) );
	parametry.insert( std::pair<std::string,float>("odchylenie", odchylenie) );
	
	return parametry;
}

ParametryRozkladu RozkladGaussa::oblicz() const{
	float suma = 0;
	int ilosc = 0;
	float odchylenie = 0;
	float srednia = 0;
	for ( int ii=0;ii<dane_.size();ii++ ) {
		suma+=dane_[ii];
		ilosc++;
	}
	srednia = suma/ilosc;
	for ( int ii=0;ii<dane_.size();ii++ ) {
		odchylenie += pow(dane_[ii] - srednia,2);
	}
	odchylenie/=ilosc;
	odchylenie = pow(odchylenie, 0.5);
	
	ParametryRozkladu parametry;
	parametry.insert( std::pair<std::string,float>("srednia", srednia) );
	parametry.insert( std::pair<std::string,float>("odchylenie", odchylenie) );
	
	return parametry;
}
