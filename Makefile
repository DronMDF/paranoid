
export OBJDIR=.obj

export CXX=g++
export CXXFLAGS=-std=c++0x -Wall -Wextra -Weffc++ -O2 -g0 -Ianalizer
#export CXXFLAGS=-std=c++0x -Wall -Wextra -Weffc++ -O0 -ggdb3 -Ianalizer

all: paranoid

.PHONY: check
check: test paranoid
	./test --random=1
	functional.test/runner.py $(realpath paranoid)

paranoid: ${OBJDIR}/paranoid.o ${OBJDIR}/analizer.o
	${CXX} -o $@ ${OBJDIR}/paranoid.o ${OBJDIR}/analizer.o \
		-lboost_filesystem-mt -lboost_system-mt

test: ${OBJDIR}/analizer.o ${OBJDIR}/test.o 
	${CXX} -o $@ ${OBJDIR}/test.o ${OBJDIR}/analizer.o \
		-lboost_unit_test_framework-mt -lboost_filesystem-mt -lboost_system-mt

selftest: paranoid
	find analizer analizer.test paranoid.cpp -name "*.cpp" -print \
		-exec ./paranoid ${CXXFLAGS} {} \;

${OBJDIR}/analizer.o : ${OBJDIR}
	./script/build.py $@ analizer

${OBJDIR}/test.o : ${OBJDIR}
	./script/build.py $@ analizer.test

# This is not auto dependences builds
# $CXX $CXXFLAGS -E -MM -MT ${OBJDIR}/paranoid.o paranoid.cpp
	
${OBJDIR}/paranoid.o : paranoid.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}:
	mkdir -p ${OBJDIR}

clean:
	find ./ -name "*.o" -exec rm {} \;
	rm -rf .obj
	rm -f paranoid test

