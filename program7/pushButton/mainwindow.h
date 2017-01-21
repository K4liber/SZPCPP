#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QPushButton>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_point_data.h>

namespace Ui {
    class MainWindow;
}
 
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void setWykresy(QwtPlot *wykres1, QwtPlot *w2, QWidget *okno);
    QwtPlot *getWykres1();
    QwtPlot *getWykres2();
    QPushButton *getButton();
    QPushButton *getButton2();
private slots:
    void handleButton();
    void handleButton2();
private:
	void rysujPochodna();
	void rysujCalka();
    QPushButton *m_button;
    QPushButton *m_button2;
    QwtPlot *wykres1;
    QwtPlot *wykres2;
    QWidget *okno;
    bool calka;
    bool normal;
    std::vector <double> x, y, y2,x2;
};
 
#endif // MAINWINDOW_H
