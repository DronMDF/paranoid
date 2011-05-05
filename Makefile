
LIBS = -lclangFrontend -lclangLex -lclangBasic -lLLVMMC -lLLVMSupport

saffer: saffer.o
	clang++ `llvm-config --ldflags` -o $@ $< ${LIBS}

%.o : %.cpp
	clang++ `llvm-config --cxxflags` -c -o $@ $<
