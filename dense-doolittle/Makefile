all: Main.exe

DenseMatrix.o: DenseMatrix.cc DenseMatrix.hh Matrix.hh
	g++ $< -c -g -o $@

DenseMatrixParser.o: DenseMatrixParser.cc DenseMatrixParser.hh DenseMatrix.hh
	g++ $< -c -g -o $@

LU_Dense_Doolittle.o: LU_Dense_Doolittle.cc LU_Dense_Doolittle.hh DenseMatrix.hh
	g++ $< -c -g -o $@

Main.exe: main.cc DenseMatrix.o DenseMatrixParser.o LU_Dense_Doolittle.o
	g++ -g $^ -o $@ -lstdc++fs
