#ifndef _rozklad_hpp_
#define _rozklad_hpp_
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>

// Mapa przechowujaca obliczone estymatory rozkladu: opis-wartosc
typedef std::map <std::string, float> ParametryRozkladu;

class Rozklad
{
	public:
		// ATD - klasa bazowa dla "obliczaczy" estymatorow
		// ustawia referencje na dane do analizy
		explicit Rozklad (const std::vector <float> &dane);
		virtual ~Rozklad () {}
		// oblicza estymatory i zwraca je w mapie
		virtual ParametryRozkladu oblicz () const = 0;
	protected:
		// przechowuje referencje na dane do analizy
		const std::vector <float> &dane_;
};

class RozkladGaussa : public Rozklad
{
	public:
		// nie robi nic sensownego poza wywolaniem konstr. klasy bazowej z odpowiednim parametrem
		explicit RozkladGaussa (const std::vector <float> &dane);
		virtual ~RozkladGaussa () {}
		// liczy wartosc srednia i odchylenie standardowe
		virtual ParametryRozkladu oblicz () const;
		// statyczna met. tworzaca i zwracajaca wskaznik na obiekt wlasnego typu
		static Rozklad* kreator (const std::vector <float> &dane);
};

class RozkladPoissona : public Rozklad
{
	public:
		// nie robi nic sensownego poza wywolaniem konstr. klasy bazowej z odpowiednim parametrem
		explicit RozkladPoissona (const std::vector <float> &dane);
		virtual ~RozkladPoissona () {}
		// liczy wartosc srednia i odchylenie standardowe
		virtual ParametryRozkladu oblicz () const;
		// statyczna met. tworzaca i zwracajaca wskaznik na obiekt wlasnego typu
		static Rozklad* kreator (const std::vector <float> &dane);
};

class RozkladLorentza : public Rozklad
{
	public:
		// nie robi nic sensownego poza wywolaniem konstr. klasy bazowej z odpowiednim parametrem
		explicit RozkladLorentza (const std::vector <float> &dane);
		virtual ~RozkladLorentza () {}
		// liczy wartosc srednia i odchylenie standardowe
		virtual ParametryRozkladu oblicz () const;
		// statyczna met. tworzaca i zwracajaca wskaznik na obiekt wlasnego typu
		static Rozklad* kreator (const std::vector <float> &dane);
};

//wskaznik typu KreatorRozkladu do funkcji tworzacej obiekt
//obliczacza rozkladu (pochodna klasy Rozklad)
typedef Rozklad* (*KreatorRozkladu)(const std::vector <float> &);

class FabrykaRozkladow // FABRYKA! :)
{
	private:
		// przechowuje wskaźniki kreatorow (funkcji tworzących!)
		static std::map <unsigned, KreatorRozkladu> rozklady;
		// przechowuje nazwy rozkladow
		static std::map <unsigned, std::string> nazwy;
		static int index;
	public:
		// rejestruje kreator danego rozkladu (id generowane przyrostowo od 1)
		static void rejestruj (KreatorRozkladu kr, const std::string &nazwa);
		// wola kreator dla rozkladu o wybranym id
		static Rozklad *utworz (unsigned id, const std::vector <float> &dane);
		// zwraca nazwe rozkladu o identyfikatorze id
		static std::string nazwa (unsigned id);
		// zwraca liczbe zarejestrowanych rozkladow
		static unsigned ilosc ();
};

#endif
