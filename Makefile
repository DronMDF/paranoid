
LIBS = -lclangFrontend -lclangLex -lclangParse -lclangSema -lclangAnalysis \
	-lclangAST -lclangSerialization -lclangDriver -lclangBasic \
	-lLLVMMC -lLLVMSupport

saffer: saffer.o
	clang++ `llvm-config --ldflags` -o $@ $< ${LIBS}

%.o : %.cpp
	clang++ `llvm-config --cxxflags` -O0 -ggdb3 -c -o $@ $<

clean:
	rm saffer *.o
