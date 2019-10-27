#include "functions.h"

matrixVec
MatrixMultiplication(matrixVec A, matrixVec B) {
	// if matrices are not compatible for multiplication, exit the program
	if (A[0].size() != B.size()) {
		cout << "MatrixMultiplication: matrices are not multiplicable. Exiting...\n";
		exit(1);
	}

	// create a vector with rows = a rows, cols = b cols
	matrixVec C(A[0].size(), vector<uint64_t>(B.size()));

	// go through each row
	for (size_t i = 0; i < A.size(); i++) {
		// go through each column
		for (size_t j = 0; j < B[0].size(); j++) {
			uint64_t sum = 0;

			// calculate products and sums for dot product
			for (size_t k = 0; k < B.size(); k++) {
				sum += A[i][k] * B[k][j];
				C[i][j] = sum;
			}
		}
	}
	return C;
}

void printMatrix(matrixVec v) {
	// debugging method for looping through and printing matrix
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v[0].size(); j++) {
			cout << v[i][j] << " ";
		}
		cout << "\n";
	}
}

uint64_t FibMatrix(uint64_t x) {
	if (x == 0) return 1;

	// declare matrices
	matrixVec squareMatrix(2, vector<uint64_t>(2, 1)),
		f0f1(2, vector<uint64_t>(1, 1)), // base case matrix
		resultMatrix;

	squareMatrix[0][0] = 0; // [[0,1],[1,1]] for matrix powers

	// dot product of squareMatrix^x and base case matrix
	resultMatrix = MatrixMultiplication(MatrixPower(squareMatrix, x), f0f1);

	return resultMatrix[0][0];
}


matrixVec MatrixPower(matrixVec matrix, int power) {
	// if matrices are not compatible for multiplication, exit the program
	if (matrix.size() != matrix[0].size()) {
		cout << "MatrixPower: matrix is not square. Exiting...\n";
		exit(1);
	}

	matrixVec ans;

	while (power > 0) {
		if (power & 1) {
			// we could use the identity matrix if ans empty,
			// but this is a bit easier
			// set ans to matrix or multiply by matrix ans
			ans = ans.empty() ? matrix : MatrixMultiplication(matrix, ans);
		}

		// get power from bit
		power >>= 1;
		// calculate matrix power
		matrix = MatrixMultiplication(matrix, matrix);
	}

	return ans;
}


uint64_t FibLoop(size_t x) {
	// set fib(0) and fib(1) as base cases
	vector<uint64_t> fibs{ 1, 1 };

	// if answer is cached, return it
	if (fibs.size() > x) {
		return fibs[x];
	}

	// iterate through from 2 to input, calculate fibonaccis
	for (size_t i = 2; i <= x; i++) {
		if (fibs.size() <= i) {
			fibs.push_back(fibs[i - 1] + fibs[i - 2]);
		}
	}
	return fibs[x];
}

uint64_t FibRecur(uint64_t x) {
	// base case
	if (x < 2) return 1;

	//otherwise recursively find answer
	return FibRecur(x - 1) + FibRecur(x - 2);
}

uint64_t FibRecurDP(size_t x) {
	// vector cache
	vector<uint64_t> fibs{ 1, 1 };
	return FibRecurDPWorker(x, fibs);
}

uint64_t FibRecurDPWorker(size_t x, vector<uint64_t> &xs) {
	if (x < 2) return 1;

	uint64_t ans;

	if (xs.size() > x) {
		return xs[x];
	}

	ans = FibRecurDPWorker(x - 1, xs) + FibRecurDPWorker(x - 2, xs);
	xs.push_back(ans);
	return ans;
}
