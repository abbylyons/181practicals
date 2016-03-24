//matrixops.h

#include "scanner.h"

typedef struct node
{
	int * matrix;
	struct node * next;
} node;

class MatrixOps
{
	public:
		MatrixOps();
		~MatrixOps();
		Scanner conventionalMatrixMult(Scanner A, Scanner B, bool outColMajor);
		Scanner addMatrices(Scanner A, Scanner B, bool outColMajor);
		Scanner subtractMatrices(Scanner A, Scanner B, bool outColMajor);
		Scanner strassens(Scanner A, Scanner B);
	private:
		node * m_data;
};
