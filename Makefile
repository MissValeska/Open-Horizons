LDLIBS=-lIrrlicht
# LDFLAGS=-L ~/Downloads/irrlicht-trunk/lib/Linux
LIBS=-lIrrlicht
# EXTRA_CXXFLAGS=-I ~/Downloads/irrlicht-trunk/include -D_LOCAL_IRRLICHT
CXX=g++
CXXFLAGS= -std=c++11 -Wall -g
GAMEBIN=OpenHorizons
# Discarded switches:  -lXxf86vm -lGL -lX11 -lXcursor -D_IRR_STATIC_LIB_

all: ${GAMEBIN}

${GAMEBIN}: main.o DriverSelectionConfiguration.o
	${CXX} ${LDFLAGS} ${LIBS} $^ -o $@

.PHONY: clean

clean:
	rm -f *.o ${GAMEBIN}
