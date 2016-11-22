CXX=g++
CXXFLAGS=-O2 -Wall -pedantic
LIBS=-lboost_regex `ncurses5-config --libs`
program04:	main.o gfx.o piec.o kontrolka_temperatury.o komendy.o
		$(CXX) -o program04 gfx.o main.o piec.o kontrolka_temperatury.o komendy.o $(LIBS) $(CXXFLAGS)
main.o:	main.cpp
		$(CXX) -o main.o -c main.cpp $(CXXFLAGS)
gfx.o: gfx.cpp gfx.hpp
		$(CXX) -o gfx.o -c gfx.cpp $(CXXFLAGS)
piec.o: piec.cpp piec.hpp
		$(CXX) -o piec.o -c piec.cpp $(CXXFLAGS)
kontrolka_temperatury.o: kontrolka_temperatury.cpp kontrolka_temperatury.hpp
		$(CXX) -o kontrolka_temperatury.o -c kontrolka_temperatury.cpp $(CXXFLAGS)
komendy.o: komendy.cpp komendy.hpp piec.hpp
		$(CXX) -o komendy.o -c komendy.cpp $(CXXFLAGS)
clean:
		rm -f *.o
