
SOURCES=${wildcard *.cpp}
OBJECTS=${SOURCES:.cpp=.o}

CXX=clang++
#CXX=g++
CXXFLAGS=-Wall -Wextra -ggdb3 -O0

paranoid: ${OBJECTS} analizer/analizer.o
	${CXX} -o $@  ${OBJECTS} analizer/analizer.o

.PHONY: analizer/analizer.o
analizer/analizer.o : 
	make -C analizer CXX="${CXX}" CXXFLAGS="${CXXFLAGS}"

%.o : %.cpp
	${CXX} -MMD -MF ${<:.cpp=.dep} ${CXXFLAGS} -Weffc++ -c -o $@ $<

libtest.a:
	${CXX} ${CXXFLAGS} -Igoogle-test/include -Igoogle-test \
		-c google-test/src/gtest-all.cc -o gtest-all.o
	${CXX} ${CXXFLAGS} -Igoogle-test/include -Igoogle-test \
		-Igoogle-mock/include -Igoogle-mock \
		-c google-mock/src/gmock-all.cc -o gmock-all.o
	ar -r $@ gtest-all.o gmock-all.o

check:  libtest.a paranoid
	make -C analizer.test CXX="${CXX}" CXXFLAGS="${CXXFLAGS}" check
	#functional.test/runner.py $(realpath paranoid)

clean:
	find ./ -name "*.o" -exec rm {} \;
	find ./ -name "*.dep" -exec rm {} \;
	rm -f paranoid libtest.a

-include ${SOURCES:.cpp=.dep}
