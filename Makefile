  
CXX = g++
CXXFLAGS = -g -Wall

all: tp1 clean

tp1: main.o complex.o cmdline.o pixel.o image.o
	$(CXX) $(CXXFLAGS) -o tp1 main.o complex.o cmdline.o pixel.o image.o

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

calculator.o:  calculator.cpp calculator.h 
	$(CXX) $(CXXFLAGS) -c calculator.cpp -o calculator.o

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err