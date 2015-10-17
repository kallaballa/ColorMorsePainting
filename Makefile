ifdef JAVASCRIPT
CXX     := em++
endif
ifdef JAVASCRIPT
TARGET  := colorMorsePainting.html
else
TARGET  := colorMorsePainting 
endif
SRCS    := ColorMorsePainting.cpp
OBJS    := ${SRCS:.cpp=.o} 
DEPS    := ${SRCS:.cpp=.dep} 

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CXXFLAGS = -std=c++0x -pedantic -Wall -O3
else
	CXXFLAGS = -std=c++0x -pedantic -Wall -O3
endif

LIBS    =

.PHONY: all clean distclean 

all: release

release: ${TARGET}

${TARGET}: ${OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.cpp %.dep 
	${CXX} ${CXXFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

clean:
	rm -f *~ *.o *.dep ${TARGET} colorMorsePainting.js colorMorsePainting.html

distclean: clean

