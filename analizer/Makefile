

SOURCES=${wildcard *.cpp}
OBJECTS=${addsuffix .o, ${basename ${SOURCES}}}

CXX?=clang++
CXXFLAGS=-Wall -Wextra -ggdb3 -O0 -I../google-test/include

all: ../analizer.o

../analizer.o: ${OBJECTS}
	ld -Ur -o $@ ${OBJECTS}

%.o : %.cpp
	${CXX} ${CXXFLAGS} -Weffc++ -c -o $@ $<
