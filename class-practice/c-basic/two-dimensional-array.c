#include <stdio.h>
#include <stdlib.h>

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

			*(C + i*N +j) = *(A + i*N + j) + *(B + i*N + j);
		}
	}


	printf("C = \n");
	for (i=0; i<M; i++){
		for (j= 0; j<N; j++){
			printf("%d\t", *(C+N*i+j));
		}
		printf("\n");
	}



	free(A);
	free(B);
	free(C);

	return 0;
}