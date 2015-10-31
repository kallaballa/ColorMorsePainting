ifdef JAVASCRIPT
CXX     := em++
endif
ifdef JAVASCRIPT
TARGET  := colorMorsePainting.html
else
TARGET  := colorMorsePainting 
endif
SRCS    := ColorMorsePainting.cpp Util.cpp Morse.cpp Color.cpp SVGMorseWriter.cpp CIEDE2000.cpp
OBJS    := ${SRCS:.cpp=.o} 
DEPS    := ${SRCS:.cpp=.dep} 

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CXXFLAGS = -std=c++0x -pedantic -Wall -O3
else
	CXXFLAGS = -std=c++0x -pedantic -Wall -O3
endif

LIBS    = -lboost_program_options

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
	rm -f *~ *.o *.dep ${TARGET} colorMorsePainting.js colorMorsePainting.html

distclean: clean

