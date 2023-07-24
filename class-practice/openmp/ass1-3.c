// Version sum of array with reduction
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


int main()
{
	int N = 16;
	int *A,i, id;
	A = (int *)malloc(N * sizeof(int));
	for (i=0;i<N;i++){
		*(A + i) = i;
	}

	printf("A: ");
	for (i=0; i<N;i++){
		printf("%d ", *(A+i));
	}
	printf("\n");

	int p = N / 2;
	while (p >= 1){
		int *B = (int *)malloc(p * sizeof(int));
		omp_set_num_threads(p);
		#pragma omp parallel private(id)
		{
			 id = omp_get_thread_num();
			*(B + id) = *(A + 2*id) + *(A + 2*id + 1);
		}

		free(A);
		A = B;
		p = p / 2;
		
	}

	int sum = *(A); // Sum at 1
	printf("Sum of the array A: %d\n", sum);
	return 0;
}


