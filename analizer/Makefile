
OBJDIR=../.obj/analizer
DEPDIR=../.dep/analizer

SOURCES=${wildcard *.cpp}
OBJECTS=${addprefix ${OBJDIR}/, ${SOURCES:.cpp=.o}}

all: analizer.o

analizer.o: ${OBJECTS}
	ld -Ur -o $@ ${OBJECTS}

${OBJDIR}/%.o : %.cpp | ${DEPDIR} ${OBJDIR}
	${CXX} -MMD -MF ${DEPDIR}/${<:.cpp=.dep} ${CXXFLAGS} -c -o $@ $<

%.h:	# Special target for handle moved include
	grep -l $@ ${DEPDIR}/* | xargs rm

${DEPDIR}:
	mkdir -p ${DEPDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}

-include ${addprefix ${DEPDIR}/, ${SOURCES:.cpp=.dep}}
