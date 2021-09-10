all: Main.exe

DenseMatrix.o: DenseMatrix.cc DenseMatrix.hh Matrix.hh
	g++ $< -c -g -o $@

DenseMatrixParser.o: DenseMatrixParser.cc DenseMatrixParser.hh DenseMatrix.hh
	g++ $< -c -g -o $@

LU_Dense_Gaussian.o: LU_Dense_Gaussian.cc LU_Dense_Gaussian.hh DenseMatrix.hh
	g++ $< -c -g -o $@

Main.exe: main.cc DenseMatrix.o DenseMatrixParser.o LU_Dense_Gaussian.o
	g++ -g $^ -o $@ -lstdc++fs
