 

SOURCES=${wildcard *.cpp}
OBJECTS=${addsuffix .o, ${basename ${SOURCES}}}
LIBS=-L../ -ltest

CXX?=clang++
CXXFLAGS=-Wall -Wextra -ggdb3 -O0 -I../google-test/include -I../analizer

all: runner

check: runner
	./$< --gtest_shuffle --gtest_random_seed=0 


runner: ${OBJECTS}
	${CXX} -pthread -o $@ ${OBJECTS} ../analizer/analizer.o ${LIBS}

%.o : %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

clean:
	rm -rf runner *.o
