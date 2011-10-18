
OBJDIR=.obj
DEPDIR=.dep

SOURCES=${wildcard *.cpp}
OBJECTS=${addprefix ${OBJDIR}/, ${SOURCES:.cpp=.o}}

#CXX=clang++
CXX=g++
CXXFLAGS=-std=c++0x -Wall -Wextra -Weffc++ -ggdb3 -O0

paranoid: ${OBJECTS} analizer/analizer.o
	${CXX} -o $@  ${OBJECTS} analizer/analizer.o -lboost_filesystem-mt

.PHONY: analizer/analizer.o
analizer/analizer.o : 
	make -C analizer CXX="${CXX}" CXXFLAGS="${CXXFLAGS}"

.PHONY: check
check: analizer/analizer.o #paranoid
	make -C analizer.test CXX="${CXX}" CXXFLAGS="${CXXFLAGS}" check
	#functional.test/runner.py $(realpath paranoid)

${OBJDIR}/%.o : %.cpp | ${DEPDIR} ${OBJDIR}
	${CXX} -MMD -MF ${DEPDIR}/${<:.cpp=.dep} ${CXXFLAGS} -c -o $@ $<

${DEPDIR}:
	mkdir -p ${DEPDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}

clean:
	find ./ -name "*.o" -exec rm {} \;
	find ./ -name "*.dep" -exec rm {} \;
	rm -rf .dep
	rm -rf .obj
	rm -f paranoid

-include ${addprefix $(OBJDIR)/, ${SOURCES:.cpp=.dep}}
