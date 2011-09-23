
LIBS = -lclangFrontend -lclangLex -lclangParse -lclangSema -lclangAnalysis \
	-lclangAST -lclangSerialization -lclangDriver -lclangBasic \
	-lLLVMMC -lLLVMSupport

CXX=clang++
#CXX=g++
CXXFLAGS=-Wall -Wextra -ggdb3 -O0

saffer: saffer.o
	${CXX} `llvm-config --ldflags` -o $@ $< ${LIBS}

%.o : %.cpp
	${CXX} `llvm-config --cxxflags` ${CXXFLAGS} -Weffc++ -c -o $@ $<

libtest.a:
	${CXX} ${CXXFLAGS} -Igoogle-test/include -Igoogle-test \
		-c google-test/src/gtest-all.cc -o gtest-all.o
	${CXX} ${CXXFLAGS} -Igoogle-test/include -Igoogle-test \
		-Igoogle-mock/include -Igoogle-mock \
		-c google-mock/src/gmock-all.cc -o gmock-all.o
	ar -r $@ gtest-all.o gmock-all.o

check: saffer
	make -C clang.unittest check
	functional.test/runner.py $(realpath saffer)

clean:
	rm -f saffer *.o libtest.a
