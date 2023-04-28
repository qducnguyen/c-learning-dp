#include <stdio.h>
#include <limits.h>
int main()
{
	int N = 10;
	int A[N], min, max, minarg, maxarg, i;
	min = INT_MAX;
	max = INT_MIN;

	for (i=0; i<N; i++){
		printf("A[%d] = ", i);
		scanf("%d", &A[i]);
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
		printf("%d \t", A[i]);
	}

	printf("\n");

	printf("Min Value = %d at %d\n", min, minarg);
	printf("Max Value = %d at %d", max, maxarg);

	printf("\n");

	return 0;
}