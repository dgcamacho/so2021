CXX = g++
CXXFLAGS = -O2 -std=c++14

OBJECTS = main.o polynomial.o rational.o matrix.o

exercise3: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

main.o: main.cc main.hh polynomial.hh rational.hh matrix.hh almost_equal.hh
	$(CXX) $(CXXFLAGS) -c $<

%.o: %.cc %.hh almost_equal.hh
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf exercise3 $(OBJECTS)
