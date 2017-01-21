#include <QtWidgets/QApplication>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_point_data.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <cmath>

std::vector <double> x, y, y2;

void loadData(std::istream &plik) {
	char line[100];
	//Wczytywanie danych ze standardowego wejscia do blng_
	while (plik.getline(line,100)) {
		std::vector<char*> callData;
		char* chars_array = strtok(line, "\t");
		while (chars_array)
		{
			callData.push_back(chars_array);
			chars_array = strtok(NULL, "\t");
		}
		

		std::istringstream ss( callData[1] );
		double n;
		ss >> n;
		x.push_back(atof(callData[0]));
		y.push_back(n);
	}
}

void fitParameters(double& a, double& b) {

    double xsum=0,x2sum=0,ysum=0,xysum=0;

    for ( unsigned int i=0;i<x.size();i++)
    {
        xsum=xsum+x[i];                        //calculate sigma(xi)
        ysum=ysum+y[i];                        //calculate sigma(yi)
        x2sum=x2sum+pow(x[i],2);                //calculate sigma(x^2i)
        xysum=xysum+x[i]*y[i];                    //calculate sigma(xi*yi)
    }
    a=(x.size()*xysum-xsum*ysum)/(x.size()*x2sum-xsum*xsum);            //calculate slope
    b=(x2sum*ysum-xsum*xysum)/(x2sum*x.size()-xsum*xsum);            //calculate intercept
	
}

void countY2(double a, double b) {
	
	for ( unsigned int ii=0;ii<x.size();ii++) {
		y2.push_back(a*x[ii]+b);
	}
	
}


int main (int argc, char *arg[])
{
	QApplication app (argc, arg);// Tworzenie okna programu
	QWidget okno;
	okno.setWindowTitle ("Dopasowanie MNK"); // ustawia tytuł okna
	okno.setFixedSize (600, 600); // rozmiar okna 800x800
	
	// Tworzenie wykresu na konkretnym oknie
	QwtPlot wykres (&okno);
	// Ustawienie tytułu wykresu
	wykres.setTitle ("Dopasowanie MNK");
	// Ustawienia tytułów osi: yLeft, yRight, xBottom, xTop
	wykres.setAxisTitle (QwtPlot::xBottom, "Nr kanału");
	wykres.setAxisTitle (QwtPlot::yLeft, "Napięcie / V");
	// Ustawienie rozmiarów wykresu
	wykres.setFixedSize (550, 550);
	// Ustawienie koloru tła
	wykres.setCanvasBackground(QBrush (QColor (0xff,0xfa, 0x6b)));
	// Ustawienie zakresu osi
	float min_x = 0;
	float min_y = 0;
	float max_x = 4200;
	float max_y = 5.5;
	wykres.setAxisScale (QwtPlot::xBottom, min_x, max_x);
	wykres.setAxisScale (QwtPlot::yLeft, min_y, max_y);
	
	double a,b;
	loadData(std::cin);
	fitParameters(a,b);
	countY2(a,b);
	std::cout<<a<<"\t"<<b<<std::endl;
	QwtPlotCurve dane_doswiadczalne;
	// Wprowadzenie punktów pomiarowych (dwie możliwości)
	//dane_doswiadczalne.setRawSamples (x.data(), y.data(), x.size()); // oryginalne tablice
	dane_doswiadczalne.setSamples (x.data(), y.data(), x.size()); // twarde kopie danych
	// Ustawienie stylu QwtPlotCurve: Lines, Sticks, Steps, Dots
	dane_doswiadczalne.setStyle (QwtPlotCurve::Dots);
	// Ustawienie „pióra”: kolor, grubość:
	dane_doswiadczalne.setPen (QPen (Qt::blue, 3));
	// Dołączenie serii do istniejącego wykresu
	dane_doswiadczalne.attach (&wykres);
	
	QwtPlotCurve dopasowanie;
	// Wprowadzenie punktów pomiarowych (dwie możliwości)
	//dane_doswiadczalne.setRawSamples (x.data(), y.data(), x.size()); // oryginalne tablice
	dopasowanie.setSamples (x.data(), y2.data(), x.size()); // twarde kopie danych
	// Ustawienie stylu QwtPlotCurve: Lines, Sticks, Steps, Dots
	dopasowanie.setStyle (QwtPlotCurve::Lines);
	// Ustawienie „pióra”: kolor, grubość:
	dopasowanie.setPen (QPen (Qt::red, 2));
	// Dołączenie serii do istniejącego wykresu
	dopasowanie.attach (&wykres);
	
	okno.show();// (...) rysowanie na oknie
	
	return app.exec();
}
