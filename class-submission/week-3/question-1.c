#include <stdio.h>
#include <stdlib.h>



int main()
{
	int N;
	int *A;
	int sum = 0;

	printf("Number of elements in array A: ");
	scanf("%d", &N);

	printf("Input array elements: ");

	A = (int *)malloc(N*sizeof(int));

	int i;
	for(i=0; i<N; i++){
		scanf("%d", (A+i));
		sum += *(A+i);
	}


	printf("Sum of the array A is: %d\n", sum);


	free(A);
}