 

SOURCES=${wildcard *.cpp}
OBJECTS=${SOURCES:.cpp=.o}
SUT_OBJECTS=../analizer/analizer.o ../CommandLine.o
IFLAGS = -I.. -I../analizer
LFLAGS = -lboost_test_exec_monitor-mt

all: runner

check: runner
	./$< --random=1

runner: ${OBJECTS} ${SUT_OBJECTS}
	${CXX} -pthread -o $@ ${OBJECTS} ${SUT_OBJECTS} ${LFLAGS}

%.o : %.cpp
	${CXX} -MMD -MF ${<:.cpp=.dep} ${CXXFLAGS} ${IFLAGS} -c -o $@ $<

-include ${SOURCES:.cpp=.dep}
