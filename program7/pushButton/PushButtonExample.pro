QT       += core gui
 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
 
TARGET = PushButtonExample
TEMPLATE = app
 
SOURCES += main.cpp \
        mainwindow.cpp
 
HEADERS  += mainwindow.h
LIBS += -L/usr/local/lib -lqwt-qt5