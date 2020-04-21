CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

ex: driver.cpp main_window.cpp
	$(CXX) $(CXXFLAGS) -o drivercode driver.cpp main_window.cpp $(GTKFLAGS)
