#include "mainwindow.h"
 
#include <QCoreApplication>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
	calka = true;
	normal = true;
    // Create the button, make "this" the parent
    m_button = new QPushButton("Load", this);
    m_button->setGeometry(QRect(QPoint(0, 0),
    QSize(200, 40)));
    
    m_button2 = new QPushButton("Pochodna", this);
    m_button2->setGeometry(QRect(QPoint(200, 0),
    QSize(200, 40)));
    
    wykres1 = new QwtPlot();
    wykres1->setFixedSize (450, 450);
	wykres1->setCanvasBackground(QBrush (QColor (0xff,0xfa, 0x6b)));
	wykres1->setTitle ("Data");
	
	wykres2 = new QwtPlot();
    wykres2->setFixedSize (450, 450);
	wykres2->setCanvasBackground(QBrush (QColor (0xff,0xfa, 0x6b)));
	wykres2->setTitle ("Całka");
 
    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));
    connect(m_button2, SIGNAL (released()), this, SLOT (handleButton2()));
}
 
void MainWindow::handleButton()
{
	y.clear();
	x.clear();
	fstream file;
    QStringList fonts = QFileDialog::getOpenFileNames(m_button, "Select a file to open...", QDir::homePath());
    for (int ii=0;ii<fonts.size();ii++) {
		std::cout<<fonts.at(ii).toLocal8Bit().constData() <<std::endl;
		file.open(fonts.at(ii).toLocal8Bit().constData(),fstream::in);
    }
    char line[100];
	//Wczytywanie danych ze standardowego wejscia do blng_
	while (file.getline(line,100)) {
		std::vector<char*> callData;
		char* chars_array = strtok(line, "\t");
		while (chars_array)
		{
			callData.push_back(chars_array);
			chars_array = strtok(NULL, "\t");
		}
		
		istringstream ssx( callData[0] );
		double nx;
		ssx >> nx;
		
		istringstream ss( callData[1] );
		double n;
		ss >> n;
		x.push_back(nx);
		y.push_back(n);
	}
	
	QwtPlotCurve dane_doswiadczalne;
	// Wprowadzenie punktów pomiarowych (dwie możliwości)
	dane_doswiadczalne.setRawSamples (x.data(), y.data(), x.size()); // oryginalne tablice
	//dane_doswiadczalne.setSamples (x.data(), y.data(), x.size()); // twarde kopie danych
	// Ustawienie stylu QwtPlotCurve: Lines, Sticks, Steps, Dots
	dane_doswiadczalne.setStyle (QwtPlotCurve::Dots);
	// Ustawienie „pióra”: kolor, grubość:
	dane_doswiadczalne.setPen (QPen (Qt::blue, 3));
	// Dołączenie serii do istniejącego wykresu
	dane_doswiadczalne.attach (wykres1);
	
	float min_x = *std::min_element(x.begin(), x.end());
	float min_y = *std::min_element(y.begin(), y.end());
	float max_x = *std::max_element(x.begin(), x.end());
	float max_y = *std::max_element(y.begin(), y.end());
	
	wykres1->setAxisScale (QwtPlot::xBottom, min_x, max_x);
	wykres1->setAxisScale (QwtPlot::yLeft, min_y, max_y);
	wykres1->replot();
	wykres1->update();
	wykres1->repaint();
	qApp->processEvents();
	
	wykres1->hide();
	wykres1->show();
	this->repaint();
	this->update();
	qApp->processEvents();
	
}

void MainWindow::handleButton2()
{
	if (calka) {
		m_button2->setText("Całka");
		wykres2->setTitle ("Pochodna");
		rysujPochodna();
	}
    else {
		m_button2->setText("Pochodna");
		wykres2->setTitle ("Całka");
		rysujCalka();
	}
		
	calka = !calka;

}

void MainWindow::setWykresy(QwtPlot *w1, QwtPlot *w2, QWidget *okno) {
	this->wykres1 = w1;
	this->wykres1 = w2;
	this->okno = okno;
}

QwtPlot *MainWindow::getWykres1(){
	return wykres1;
}

QwtPlot *MainWindow::getWykres2(){
	return wykres2;
}

QPushButton *MainWindow::getButton() {
	return m_button;
}

QPushButton *MainWindow::getButton2() {
	return m_button2;
}

void MainWindow::rysujPochodna() {
	y2.clear();
	wykres2->replot();
	for ( unsigned int ii=1;ii<x.size();ii++ ) {
		double yVal = (y[ii] - y[ii-1])/(x[ii] - x[ii-1]);
		y2.push_back(yVal);
	}
	
	QwtPlotCurve dane_doswiadczalne;
	// Wprowadzenie punktów pomiarowych (dwie możliwości)
	//dane_doswiadczalne.setRawSamples (x.data(), y.data(), x.size()); // oryginalne tablice
	dane_doswiadczalne.setSamples (x.data(), y2.data(), x.size()); // twarde kopie danych
	// Ustawienie stylu QwtPlotCurve: Lines, Sticks, Steps, Dots
	dane_doswiadczalne.setStyle (QwtPlotCurve::Dots);
	// Ustawienie „pióra”: kolor, grubość:
	dane_doswiadczalne.setPen (QPen (Qt::blue, 3));
	// Dołączenie serii do istniejącego wykresu
	dane_doswiadczalne.attach (wykres2);
	
	float min_x = *std::min_element(x.begin(), x.end());
	float min_y = *std::min_element(y2.begin(), y2.end());
	float max_x = *std::max_element(x.begin(), x.end());
	float max_y = *std::max_element(y2.begin(), y2.end());
	
	wykres2->setAxisScale (QwtPlot::xBottom, min_x, max_x);
	wykres2->setAxisScale (QwtPlot::yLeft, min_y, max_y);
	wykres2->replot();
	wykres2->update();
	wykres2->repaint();
	qApp->processEvents();
	
	wykres2->hide();
	wykres2->show();
	this->repaint();
	this->update();
	qApp->processEvents();
}

void MainWindow::rysujCalka() {
	QwtPlotCurve dane_doswiadczalne;
	y2.clear();
	x2.push_back(1);
	x2.clear();
	//dane_doswiadczalne.setSamples(x2,y2);
	wykres2->replot();
	for ( unsigned int ii=1;ii<x.size();ii++ ) {
		double yVal = 0;
		for ( unsigned int jj=1;jj<=ii;jj++ ) {
			yVal += (y[jj-1] + y[jj])*(x[jj] - x[jj-1])/2;
		}
		y2.push_back(yVal);
	}
	
	
	// Wprowadzenie punktów pomiarowych (dwie możliwości)
	//dane_doswiadczalne.setRawSamples (x.data(), y.data(), x.size()); // oryginalne tablice
	dane_doswiadczalne.setSamples (x.data(), y2.data(), x.size()); // twarde kopie danych
	// Ustawienie stylu QwtPlotCurve: Lines, Sticks, Steps, Dots
	dane_doswiadczalne.setStyle (QwtPlotCurve::Dots);
	// Ustawienie „pióra”: kolor, grubość:
	dane_doswiadczalne.setPen (QPen (Qt::blue, 3));
	// Dołączenie serii do istniejącego wykresu
	dane_doswiadczalne.attach (wykres2);
	
	float min_x = *std::min_element(x.begin(), x.end());
	float min_y = *std::min_element(y2.begin(), y2.end());
	float max_x = *std::max_element(x.begin(), x.end());
	float max_y = *std::max_element(y2.begin(), y2.end());
	
	wykres2->setAxisScale (QwtPlot::xBottom, min_x, max_x);
	wykres2->setAxisScale (QwtPlot::yLeft, min_y, max_y);
	wykres2->replot();
	wykres2->update();
	wykres2->repaint();
	qApp->processEvents();
	
	wykres2->hide();
	wykres2->show();
	this->repaint();
	this->update();
	qApp->processEvents();
}
