
OBJDIR=../.obj/analizer.test
DEPDIR=../.dep/analizer.test

SOURCES=${wildcard *.cpp}
OBJECTS=${addprefix ${OBJDIR}/, ${SOURCES:.cpp=.o}}
SUT_OBJECTS=../analizer/analizer.o ../CommandLine.o
IFLAGS = -I.. -I../analizer
LFLAGS = -lboost_test_exec_monitor-mt -lboost_regex-mt

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

-include ${addprefix $(OBJDIR)/, ${SOURCES:.cpp=.dep}}
