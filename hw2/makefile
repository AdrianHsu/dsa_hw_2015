target = demo HashNode
CPPFLAGS = -O3 -g -std=c++11 -Wall

all: demo

demo: demo.cpp HashNode.cpp HashNode.h
	g++ $(CPPFLAGS) demo.cpp  HashNode.cpp -o $@

clean:
	rm -rf $(target)