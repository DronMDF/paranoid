
SOURCES=${wildcard *.cpp}
OBJECTS=${SOURCES:.cpp=.o}

#CXX=clang++
CXX=g++
CXXFLAGS=-std=c++0x -Wall -Wextra -ggdb3 -O0

paranoid: ${OBJECTS} analizer/analizer.o
	${CXX} -o $@  ${OBJECTS} analizer/analizer.o

.PHONY: analizer/analizer.o
analizer/analizer.o : 
	make -C analizer CXX="${CXX}" CXXFLAGS="${CXXFLAGS}"

%.o : %.cpp
	${CXX} -MMD -MF ${<:.cpp=.dep} ${CXXFLAGS} -Weffc++ -c -o $@ $<


.PHONY: check
check: #paranoid
	make -C analizer.test CXX="${CXX}" CXXFLAGS="${CXXFLAGS}" check
	#functional.test/runner.py $(realpath paranoid)

clean:
	find ./ -name "*.o" -exec rm {} \;
	find ./ -name "*.dep" -exec rm {} \;
	rm -f paranoid

-include ${SOURCES:.cpp=.dep}
