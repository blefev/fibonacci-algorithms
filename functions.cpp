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
		f0f1(2, vector<uint64_t>(1, 1)), // base case matrix. f(0) = 1, f(1) = 1
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
	uint64_t a = 1, b = 1, c;

	// iterate through from 2 to x, calculate fibonaccis
	for (size_t i = 2; i <= x; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

uint64_t FibRecur(uint64_t x) {
	// base case
	if (x < 2) return 1;

	//otherwise recursively find answer
	return FibRecur(x - 1) + FibRecur(x - 2);
}

uint64_t FibRecurDP(size_t x) {
	// vector cache
	map<uint64_t, uint64_t> fibsCache{ {0, 1}, {1, 1} };
	return FibRecurDPWorker(x, fibsCache);
}

uint64_t FibRecurDPWorker(size_t x, map<uint64_t, uint64_t>&fibsCache) {
	// base case
	if (x < 2) return 1;

	uint64_t ans;

	// return answer if in cache
	if (fibsCache.find(x) != fibsCache.end()) {
		return fibsCache[x];
	}

	// recursively find answer
	ans = FibRecurDPWorker(x - 1, fibsCache) + FibRecurDPWorker(x - 2, fibsCache);
	// store answer
	fibsCache.emplace(x, ans);
	return ans;
}

uint64_t FibRecurDPTail(uint64_t x) {
	return FibRecurDPTailWorker(x);
}

uint64_t FibRecurDPTailWorker(uint64_t x, uint64_t a, uint64_t b) {
	if (x == 0) {
		return a;
	}
	return FibRecurDPTailWorker(x - 1, b, a + b);
}
