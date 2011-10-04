 

SOURCES=${wildcard *.cpp}
OBJECTS=${SOURCES:.cpp=.o}
LIBS=-L../ -ltest

IFLAGS = -I../google-test/include -I../analizer

all: runner

check: runner
	./$< --gtest_shuffle --gtest_random_seed=0 --gtest_print_time=0

runner: ${OBJECTS} ../analizer/analizer.o
	${CXX} -pthread -o $@ ${OBJECTS} ../analizer/analizer.o ${LIBS}

%.o : %.cpp
	${CXX} -MMD -MF ${<:.cpp=.dep} ${CXXFLAGS} ${IFLAGS} -c -o $@ $<

-include ${SOURCES:.cpp=.dep}
