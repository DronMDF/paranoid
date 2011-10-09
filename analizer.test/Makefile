 

SOURCES=${wildcard *.cpp}
OBJECTS=${SOURCES:.cpp=.o}
SUT_OBJECTS=../analizer/analizer.o ../CommandLine.o
LIBS=-L../ -ltest

IFLAGS = -I../google-test/include -I.. -I../analizer

all: runner

check: runner
	./$< --gtest_shuffle --gtest_random_seed=0 --gtest_print_time=0

runner: ${OBJECTS} ${SUT_OBJECTS}
	${CXX} -pthread -o $@ ${OBJECTS} ${SUT_OBJECTS} ${LIBS}

%.o : %.cpp
	${CXX} -MMD -MF ${<:.cpp=.dep} ${CXXFLAGS} ${IFLAGS} -c -o $@ $<

-include ${SOURCES:.cpp=.dep}
