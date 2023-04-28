#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main()
{
	int N = 10;
	int *A, min, max, minarg, maxarg, i;
	A = (int *) malloc(N * sizeof(int));

	min = INT_MAX;
	max = INT_MIN;

	for (i=0; i<N; i++){
		printf("A[%d] = ", i);
		scanf("%d", A+i); // A+i: address , *(A+i): value == A[i]
		if (A[i] < min){
			min = A[i];
			minarg = i;
		}

		if (A[i] > max){
			max = A[i];
			maxarg = i;
		}
	}


	for (i=0; i<N; i++){
		printf("%d \t",A[i]);
	}

	printf("\n");

	printf("Min Value = %d at %d\n", min, minarg);
	printf("Max Value = %d at %d", max, maxarg);

	printf("\n");

	free(A);

	return 0;
}