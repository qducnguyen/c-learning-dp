#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


int main()
{
	int N = 20;
	int i, *A, sum = 0;

	A = (int *)malloc(N * sizeof(int));

	for (i=0;i<N;i++){
		*(A + i) = i;
	}

	// Part 2: For calculate the sum of the array

	printf("A: ");
	for (i=0; i<N;i++){
		printf("%d ", *(A+i));
	}
	printf("\n");

	// Not parallel

	// for (i=0;i<N;i++){
	// 	sum += *(A+i);
	// }

	// Parallel 
	int id, nthreads, Ns,start, end, Ss[100];
	omp_set_num_threads(12);
	#pragma omp parallel private(id, start, end, i)
	{
		nthreads = omp_get_num_threads();
		Ns = N / nthreads;
		id = omp_get_thread_num();
		start = Ns*id;

		if (id != nthreads -1){
			end = start + Ns;
		}
		else{
			end = N;
		}

		Ss[id] = 0;
		for(i=start; i<end; i++){
			Ss[id] = Ss[id] + *(A+i);
		}
	}

	for (i=0; i<nthreads;i++){
		sum += Ss[i];
	}

	
	printf("Sum of the array A %d\n", sum);

	return 0;
}