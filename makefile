CXX = g++
execs = signal-echo
objects = signal-echo.o
source = signal-echo.cpp

all: $(execs)

signal-echo: $(objects)
	$(CXX) -o $(execs) $(objects)

signal-echo.o: $(source)
	$(CXX) -c $(source)	

clean:
	rm -f $(objects) $(execs)