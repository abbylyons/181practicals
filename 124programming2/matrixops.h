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
		void unload();
		Scanner conventionalMatrixMult(Scanner A, Scanner B, bool outColMajor);
		Scanner addMatrices(Scanner A, Scanner B, bool outColMajor);
		Scanner subtractMatrices(Scanner A, Scanner B, bool outColMajor);
		Scanner strassensWrapper(Scanner A, Scanner B, unsigned int crossover = 128);
		Scanner strassens(Scanner A, Scanner B, unsigned int crossover);
	private:
		node * m_data;
};