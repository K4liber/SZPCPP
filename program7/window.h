#ifndef WINDOW_H
#define WINDOW_H

#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>

class MyWidget : public QWidget
{
	Q_OBJECT
	public:
		MyWidget (QWidget* parent = 0);
 
	public slots:
		void myFunction(void);
 
	private:
		QVBoxLayout* mainLayout; 
		QHBoxLayout* buttonLayout;
		QPushButton* myButton;
}

#endif
