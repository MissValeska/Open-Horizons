LDLIBS=-lIrrlicht
LDFLAGS=-L ~/Downloads/irrlicht-trunk/include -L ~Downloads/irrlicht-trunk/source/Irrlicht
LIBS=-lIrrlicht
CXX=g++
CXXFLAGS= -std=c++11 -Wall -g  -D_IRR_STATIC_LIB_ -I ~/Downloads/irrlicht-trunk/include -I ~/Downloads/irrlicht-trunk/lib/Linux
# Discarded switches:  -lXxf86vm -lGL -lX11 -lXcursor

all: ExperimentalGame

ExperimentalGame: main.o
	${CXX} ${LDFLAGS} ${LIBS} $^ -o $@

.PHONY: clean

clean:
	rm -f *.o ExperimentalGame
