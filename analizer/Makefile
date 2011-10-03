

SOURCES=${wildcard *.cpp}
OBJECTS=${SOURCES:.cpp=.o}

all: analizer.o

analizer.o: ${OBJECTS}
	ld -Ur -o $@ ${OBJECTS}

%.o : %.cpp
	${CXX} -MMD -MF ${<:.cpp=.dep} ${CXXFLAGS} -Weffc++ -c -o $@ $<

-include ${SOURCES:.cpp=.dep}
