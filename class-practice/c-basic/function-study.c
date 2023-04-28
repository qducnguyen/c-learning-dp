#include <stdio.h>
#include <stdlib.h>
#include "function-study.h"

int main()
{
	int M = 2;
	int N = 3;
	int *A, *B, *C, i, j;
	A = (int *) malloc(M*N * sizeof(int));
	B = (int *) malloc(M*N * sizeof(int));
	C = (int *) malloc(M*N * sizeof(int));

	for (i=0; i<M; i++){
		for (j= 0; j<N; j++){
			printf("A[%d][%d] = ", i, j);
			scanf("%d", A+N*i+j);
		}
	}

	for (i=0; i<M; i++){
		for (j= 0; j<N; j++){
			printf("B[%d][%d] = ", i, j);
			scanf("%d", B+N*i+j);
		}
	}

	Add2Matric(A, B, C, M, N);

	printf("\nC = \n");
	PrintMatrix(C,M, N);



	free(A);
	free(B);
	free(C);

	return 0;
}

void PrintMatrix(int* Matrix, int Row, int Col){
	int i, j;
	for (i=0; i<Row; i++){
		for (j= 0; j<Col; j++){
			printf("%d\t", *(Matrix+Col*i+j));
		}
		printf("\n");
	}
}


void Add2Matric(int* A, int*B, int* C, int M, int N){

	int i, j;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			*(C + i*N +j) = *(A + i*N + j) + *(B + i*N + j);
		}
	}

}	