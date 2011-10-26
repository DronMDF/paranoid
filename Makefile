
OBJDIR=.obj
DEPDIR=.dep

SOURCES=${wildcard *.cpp}
OBJECTS=${addprefix ${OBJDIR}/, ${SOURCES:.cpp=.o}}

#CXX=clang++
CXX=g++
CXXFLAGS=-std=c++0x -Wall -Wextra -Weffc++ -ggdb3 -O0

paranoid: .obj/paranoid.o paranoid.o analizer/analizer.o
	${CXX} -o $@ .obj/paranoid.o paranoid.o analizer/analizer.o -lboost_filesystem-mt

paranoid.o: $(filter-out .obj/paranoid.o, ${OBJECTS})
	ld -Ur -o $@ $(filter-out .obj/paranoid.o, ${OBJECTS})

.PHONY: analizer/analizer.o
analizer/analizer.o : 
	make -C analizer CXX="${CXX}" CXXFLAGS="${CXXFLAGS}"

.PHONY: check
check: paranoid.o analizer/analizer.o paranoid
	make -C analizer.test CXX="${CXX}" CXXFLAGS="${CXXFLAGS}" check
	functional.test/runner.py $(realpath paranoid)

${OBJDIR}/%.o : %.cpp | ${DEPDIR} ${OBJDIR}
	${CXX} -MMD -MF ${DEPDIR}/${<:.cpp=.dep} ${CXXFLAGS} -c -o $@ $<

${DEPDIR}:
	mkdir -p ${DEPDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}

clean:
	find ./ -name "*.o" -exec rm {} \;
	find ./ -name "*.dep" -type f -exec rm -rf {} \;
	rm -rf .obj
	rm -rf .dep
	rm -f paranoid

build_check:
	CXX="${CXX}" CXXFLAGS="${CXXFLAGS}" ./script/build.py analizer.o analizer

-include ${addprefix ${DEPDIR}/, ${SOURCES:.cpp=.dep}}
