CXX=g++

CXXFLAGS=-W -Wall -g -std=c++11 -Wno-unused-parameter
OBJECTS=tcp_service.hpp main.cpp
LDFLAGS+=-lboost_date_time -lboost_system -lboost_thread

all: bubbled

bubbled: 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.cpp bubble.cpp tcp_client.hpp tcp_service.hpp $(LDFLAGS) -o bubbled

clean:
	$(RM) bubbled




