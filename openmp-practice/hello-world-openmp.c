#include <stdio.h>
#include <omp.h>

void main()
{	
	int i;
	int N = 1000;
	#pragma omp parallel for 
	for(i=0; i<N;i++){
		printf("Hello duc from %d index \n", i);
	}
}