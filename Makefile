  
CXX = g++
CXXFLAGS = -g -Wall

all: programa_tp0 clean

programa_tp0: main.o complex.o cmdline.o pixel.o image.o
	$(CXX) $(CXXFLAGS) -o programa_tp0 main.o complex.o cmdline.o pixel.o image.o

main.o: main.cpp  
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

cmdline.o: cmdline.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c cmdline.cpp -o cmdline.o

pixel.o: pixel.cpp pixel.h 
	$(CXX) $(CXXFLAGS) -c pixel.cpp -o pixel.o

complex.o: complex.cpp complex.h
	$(CXX) $(CXXFLAGS) -c complex.cpp -o complex.o

image.o:  image.cpp image.h 
	$(CXX) $(CXXFLAGS) -c image.cpp -o image.o

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err