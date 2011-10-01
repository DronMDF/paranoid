 

SOURCES=${wildcard *.cpp}
OBJECTS=${SOURCES:.cpp=.o}
LIBS=-L../ -ltest

CXX?=clang++
CXXFLAGS=-Wall -Wextra -ggdb3 -O0 -I../google-test/include -I../analizer

all: runner

check: runner
	./$< --gtest_shuffle --gtest_random_seed=0 --gtest_print_time=0

runner: ${OBJECTS}
	${CXX} -pthread -o $@ ${OBJECTS} ../analizer/analizer.o ${LIBS}

%.o : %.cpp
	${CXX} -MMD -MF ${<:.cpp=.dep} ${CXXFLAGS} -c -o $@ $<

-include ${SOURCES:.cpp=.dep}
