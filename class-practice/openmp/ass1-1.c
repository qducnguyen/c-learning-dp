// Some of two array

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(){
	int N = 20;
	int i, *A, *B, *C;

	A = (int *)malloc(N * sizeof(int));
	B = (int *)malloc(N * sizeof(int));
	C = (int *)malloc(N * sizeof(int));

	for (i=0;i<N;i++){
		*(A + i) = i;
		*(B + i) = 2*i;
	}

	// Part 1: For calculate the array

	// Not parallel
	// for (i=0;i<N;i++){
	// 	*(C + i) = *(A +i) + *(B +i);
	// }


	// Parallel
	int id, nthreads, Ns, start, end;
	omp_set_num_threads(12); // ? 
	#pragma omp parallel private(id, start, end, i)
	{
		nthreads = omp_get_num_threads();
		Ns = N / nthreads;

		id = omp_get_thread_num();
		start = Ns*id; 
		if (id != nthreads - 1){
			end = start + Ns;
		}
		else{
			end = N;
		}

		for (i=start; i<end;i++){
			*(C + i) = *(A + i) + *(B + i);
		}
	}


	printf("A: ");
	for (i=0; i<N;i++){
		printf("%d ", *(A+i));
	}
	printf("\n");

	printf("B: ");
	for (i=0; i<N;i++){
		printf("%d ", *(B+i));
	}
	printf("\n");

	printf("C: ");
	for (i=0; i<N;i++){
		printf("%d ", *(C+i));
	}
	printf("\n");

	return 0;
}