
OBJDIR=../.obj/analizer.test
DEPDIR=../.dep/analizer.test

SOURCES=${wildcard *.cpp}
OBJECTS=${addprefix ${OBJDIR}/, ${SOURCES:.cpp=.o}}
SUT_OBJECTS=../paranoid.o ../analizer/analizer.o
IFLAGS = -I.. -I../analizer
LFLAGS = -lboost_test_exec_monitor-mt -lboost_regex-mt -lboost_filesystem-mt

all: runner

check: runner
	./$< --random=1

runner: ${OBJECTS} ${SUT_OBJECTS}
	${CXX} -pthread -o $@ ${OBJECTS} ${SUT_OBJECTS} ${LFLAGS}

${OBJDIR}/%.o : %.cpp | ${DEPDIR} ${OBJDIR}
	${CXX} -MMD -MF ${DEPDIR}/${<:.cpp=.dep} ${CXXFLAGS} ${IFLAGS} -c -o $@ $<

${DEPDIR}:
	mkdir -p ${DEPDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}

-include ${addprefix ${DEPDIR}/, ${SOURCES:.cpp=.dep}}
