
LIBS = -lclangFrontend -lclangLex -lclangParse -lclangSema -lclangAnalysis \
	-lclangAST -lclangBasic -lLLVMMC -lLLVMSupport

saffer: saffer.o
	clang++ `llvm-config --ldflags` -o $@ $< ${LIBS}

%.o : %.cpp
	clang++ `llvm-config --cxxflags` -c -o $@ $<

clean:
	rm saffer *.o
