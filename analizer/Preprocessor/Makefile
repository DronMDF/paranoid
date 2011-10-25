
OBJDIR=../../.obj/analizer/Preprocessor
DEPDIR=../../.dep/analizer/Preprocessor

SOURCES=${wildcard *.cpp}
OBJECTS=${addprefix ${OBJDIR}/, ${SOURCES:.cpp=.o}}

all: preprocessor.o

preprocessor.o: ${OBJECTS}
	ld -Ur -o $@ ${OBJECTS}

${OBJDIR}/%.o : %.cpp | ${DEPDIR} ${OBJDIR}
	${CXX} -MMD -MF ${DEPDIR}/${<:.cpp=.dep} ${CXXFLAGS} -c -o $@ $<

${DEPDIR}:
	mkdir -p ${DEPDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}

-include ${addprefix ${DEPDIR}/, ${SOURCES:.cpp=.dep}}
