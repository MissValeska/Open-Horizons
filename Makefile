LDLIBS=-lIrrlicht
LIBS=-lIrrlicht
CXX=clang++
DEBUG=-g -Wfatal-errors -pedantic -Weffc++ -Wunreachable-code -Winline -Wredundant-decls -Wno-vla
CXXFLAGS=-std=c++11 -Wall ${DEBUG}
GAMEBIN=OpenHorizons
# Discarded switches:  -lXxf86vm -lGL -lX11 -lXcursor -D_IRR_STATIC_LIB_

all: ${GAMEBIN}

${GAMEBIN}: main.o DriverSelectionConfiguration.o
	${CXX} ${LDFLAGS} ${LIBS} $^ -o $@

.PHONY: clean

clean:
	rm -f *.o ${GAMEBIN}
