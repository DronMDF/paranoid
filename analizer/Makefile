

SOURCES=${wildcard *.cpp}
OBJECTS=${SOURCES:.cpp=.o}

CXX?=clang++
CXXFLAGS=-Wall -Wextra -Weffc++ -ggdb3 -O0 -I../google-test/include

all: analizer.o

analizer.o: ${OBJECTS}
	ld -Ur -o $@ ${OBJECTS}

%.o : %.cpp
	${CXX} -MMD -MF ${<:.cpp=.dep} ${CXXFLAGS} -Weffc++ -c -o $@ $<

-include ${SOURCES:.cpp=.dep}
