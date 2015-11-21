ifdef JAVASCRIPT
CXX     := em++
else
  ifeq ($(UNAME), Darwin)
    CXX     := g++
  else
    CXX     := clang++
  endif
endif

ifdef JAVASCRIPT
TARGET  := colorMorsePainting.html
else
TARGET  := colorMorsePainting 
endif

SRCS    := src/ColorMorsePainting.cpp src/Util.cpp src/Morse.cpp src/Color.cpp src/SVGMorseWriter.cpp src/CIEDE2000.cpp
OBJS    := ${SRCS:.cpp=.o} 
DEPS    := ${SRCS:.cpp=.dep} 

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CXXFLAGS = -std=c++11 -pedantic -Wall -O3 -I/usr/local/include
  LIBS    = -lboost_program_options-mt -L/opt/local/lib
else
	CXXFLAGS = -std=c++0x -pedantic -Wall -O3
  LIBS    = -lboost_program_options -L/opt/local/lib
endif

LIBS    = -lboost_program_options -L/usr/local/lib

.PHONY: all clean distclean 

all: release

release: ${TARGET}

debug: CXXFLAGS += -g3 -O0 -rdynamic
debug: LDFLAGS += -Wl,--export-dynamic
debug: LIBS+= -lbfd
debug: ${TARGET}

${TARGET}: ${OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.cpp %.dep 
	${CXX} ${CXXFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

clean:
	rm -f src/*~ src/*.o src/*.dep ${TARGET} colorMorsePainting.js colorMorsePainting.html

distclean: clean

