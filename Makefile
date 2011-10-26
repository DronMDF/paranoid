
export OBJDIR=.obj

export CXX=g++
export CXXFLAGS=-std=c++0x -Wall -Wextra -Weffc++ -ggdb3 -O0 \
	-I. -Ianalizer -Ianalizer/Preprocessor

all: paranoid

.PHONY: check
check: test paranoid
	./test --random=1
	functional.test/runner.py $(realpath paranoid)

paranoid: .obj/paranoid.o .obj/CommandLine.o .obj/analizer.o
	${CXX} -o $@ .obj/paranoid.o .obj/CommandLine.o .obj/analizer.o \
		-lboost_filesystem-mt

test: .obj/CommandLine.o .obj/analizer.o .obj/test.o
	${CXX} -o $@ .obj/test.o .obj/CommandLine.o .obj/analizer.o \
		-lboost_test_exec_monitor-mt -lboost_filesystem-mt -lboost_regex-mt 

.PHONY: .obj/analizer.o
.obj/analizer.o : ${OBJDIR}
	./script/build.py $@ analizer

.PHONY: .obj/test.o
.obj/test.o : ${OBJDIR}
	./script/build.py $@ analizer.test

# This is not auto dependences builds
.obj/paranoid.o : paranoid.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

.obj/CommandLine.o : CommandLine.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}:
	mkdir -p ${OBJDIR}

clean:
	find ./ -name "*.o" -exec rm {} \;
	find ./ -name "*.dep" -type f -exec rm -rf {} \;
	rm -rf .obj
	rm -rf .dep
	rm -f paranoid

