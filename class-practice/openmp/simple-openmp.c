#include <omp.h>
#include <stdio.h>

int main()
{	

	omp_set_num_threads(20); 

	#pragma omp parallel
	{ 


	int thread_num = omp_get_num_threads();
	int threadID =  omp_get_thread_num();

	printf("Hello from thread %d, nthread %d \n", threadID, thread_num);
	printf("Hello duc dep trai.\n");
	}
}