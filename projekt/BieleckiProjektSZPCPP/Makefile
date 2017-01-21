XX = g++
CXXFLAGS =-std=c++11 -lboost_system -lpthread -lboost_thread -L/usr/lib/x86_64-linux-gnu -lalleg
LIBRARIES = functional vector cstring map
CXXCASUAL = -std=c++11

flovelution:	main.o listek.o lib.o kwiatek.o generation.o stats.o
	$(CXX) -o flovelution main.o listek.o lib.o kwiatek.o generation.o stats.o $(LIBS) $(CXXFLAGS)
		
main.o:	main.cpp
	$(CXX) -o main.o -c main.cpp $(CXXCASUAL)

lib.o: lib.cpp lib.h 
	$(CXX) -o lib.o -c lib.cpp $(CXXCASUAL)

listek.o: listek.cpp listek.h 
	$(CXX) -o listek.o -c listek.cpp $(CXXCASUAL)

kwiatek.o: kwiatek.cpp kwiatek.h 
	$(CXX) -o kwiatek.o -c kwiatek.cpp $(CXXCASUAL)
	
generation.o: generation.cpp generation.h 
	$(CXX) -o generation.o -c generation.cpp $(CXXCASUAL)
	
stats.o: stats.cpp stats.h 
	$(CXX) -o stats.o -c stats.cpp $(CXXCASUAL)
	
clean:
	rm -f *.o

