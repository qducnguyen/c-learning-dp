#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check_print_number(int num){
	if (num <= 1){
		return 0;
	}
	else if (num == 2){
		return 1;
	}
	else {
		int i;
		int sqrt_num = (int)sqrt(num);
		for (i=2; i<=sqrt_num; i++){
			if (num % i == 0){
				return 0;
			}
		}

		return 1;
	}
}

int main()
{
	int N;
	// Input 
	while(1)
	{
		printf("Input number of numbers N: ");
		scanf("%d", &N);
		if ( N <= 0){
			puts("Invalid input value N, N must be positive.\n");
		}

		else {
			printf("Input: ");
			int i;
			int A[N];
			for(i=0; i<N;i++){
				scanf("%d", &A[i]);
			}

			printf("Output: ");
			for(i=0; i<N;i++){
				if (check_print_number(A[i])){
					printf("%d ", A[i]);
				}
			}

			printf("\n");

			break;
		}

	}
}

