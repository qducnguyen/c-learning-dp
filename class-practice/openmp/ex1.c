#include <omp.h>
#include <stdio.h>

int main()
{	

	int threads = 16385;
	omp_set_num_threads(threads); 

	#pragma omp parallel
	{ 
	int threadID =  omp_get_thread_num();
	printf("Hello from thread %d\n", threadID);
	}
}