
export OBJDIR=.obj

export CXX=g++
export CXXFLAGS=-std=c++0x -Wall -Wextra -Weffc++ -O2 -g0 -Ianalizer

all: paranoid

.PHONY: check
check: test paranoid
	./test --random=1
	functional.test/runner.py $(realpath paranoid)

paranoid: .obj/paranoid.o .obj/analizer.o
	${CXX} -o $@ .obj/paranoid.o .obj/analizer.o \
		-lboost_filesystem-mt

test: .obj/test.o .obj/analizer.o
	${CXX} -o $@ .obj/test.o .obj/analizer.o \
		-lboost_unit_test_framework-mt -lboost_filesystem-mt

selftest: paranoid
	find analizer analizer.test paranoid.cpp -name "*.cpp" -print \
		-exec ./paranoid ${CXXFLAGS} {} \;

.PHONY: .obj/analizer.o
.obj/analizer.o : ${OBJDIR}
	./script/build.py $@ analizer

.PHONY: .obj/test.o
.obj/test.o : ${OBJDIR}
	./script/build.py $@ analizer.test

# This is not auto dependences builds
.obj/paranoid.o : paranoid.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}:
	mkdir -p ${OBJDIR}

clean:
	find ./ -name "*.o" -exec rm {} \;
	rm -rf .obj
	rm -f paranoid test

