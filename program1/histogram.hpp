#ifndef _histogram_hpp_
#define _histogram_hpp_
#include <vector>
#include <iostream>
#include <string>

class Histogram {
	public:
		Histogram ();
		void dodaj (float x);
		size_t rozmiar () const;
		float srednia () const;
		float odchylenie () const;
		float max () const;
		float min () const;
	private:
		std::vector<float> dane_;
		mutable bool srednia_akt_;
		mutable bool odchylenie_akt_;
		mutable float srednia_;
		mutable float odchylenie_;
};

#endif
