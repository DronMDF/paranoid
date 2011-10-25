
OBJECTS = Preprocessor/preprocessor.o

all: analizer.o

analizer.o: ${OBJECTS}
	ld -Ur -o $@ ${OBJECTS}

.PHONY: Preprocessor/preprocessor.o
Preprocessor/preprocessor.o :
	make -C Preprocessor
