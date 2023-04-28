#include <stdio.h>
#include <stdlib.h>

void read_square_matrix(float *matrix, int M)
{
	int i, j;
	for(i=0; i<M; i++){
		for(j=0; j<M;j++){
			printf("A[%d][%d] = ", i, j);
			scanf("%f", matrix + i*M +j);
		}
	}

}


void print_square_matrix(float *matrix, int M)
{
	int i, j;
	for(i=0; i<M; i++){
		for(j=0; j<M;j++){
			printf(" %.4f", *(matrix + i*M + j));
		}
		printf("\n");
	}

}



float determinant(float *A, int size_matrix){
	if (size_matrix < 1){
		return 0.0;
	}
	else if(size_matrix == 1){
		return *(A);
	}
	else{
		float result = 0.0;
		float *B;
		B = (float *)malloc((size_matrix-1)*(size_matrix-1)*sizeof(float));
		int j,k, h, sign;
		
		for (j=0; j<size_matrix; j++){
			for (k=0; k< size_matrix-1; k++){
				for(h=0; h < size_matrix-1; h++){
					if (h>=j){
						*(B + k*(size_matrix-1) + h) = *(A + (k+1)*size_matrix + h+1); 
					}
					else {
						*(B + k*(size_matrix-1) + h) = *(A + (k+1)*size_matrix + h); 
	
					}

				}
			}

			if (j % 2 == 0){
				sign = 1;
			}
			else {
				sign = -1;
			}

			result += *(A + j) * sign * determinant(B, size_matrix-1);
		}

		free(B);
		return result;
	}

}


int inverse_square_matrix(float *A, float *B, int M)
{	
	float determinant_A = determinant(A, M);

	if (determinant_A == 0.0){
		return 0;
	}


	float *C;
	C = (float *)malloc((M-1)*(M-1)*sizeof(float));
	
	int i, j, h, k, a, b, a_temp, b_temp, sign;
	for(i=0; i<M;i++){
		for(j=0;j<M;j++){
			h = j;
			k = i;
			for(a=0;a < (M-1);a++){
				for(b=0; b < (M-1); b++){
					if(a >= h){
						a_temp = a + 1;
					}
					else{
						a_temp = a;
					}

					if(b >= k){
						b_temp = b + 1;
					}
					else{
						b_temp = b;
					}

					*(C + a * (M-1) + b) = *(A + a_temp* M + b_temp);		
				}
			}

			if ((h + k) % 2 == 0){
				sign = 1;
			} 
			else{
				sign = -1;
			}


			*(B + i*M + j) =  sign * determinant(C, M-1) / determinant_A;
		}
	}

	free(C);
	return 1;


}




int main()
{
	int M;
	float *A;
	float *B;

	// Read size of matrix M 
	
	printf("Input size of square matrix A: ");
	scanf("%d", &M);

	A = (float *)malloc(M*M*sizeof(float));
	B = (float *)malloc(M*M*sizeof(float));


	printf("Input matrix A: \n");
	read_square_matrix(A, M);

	printf("\n");

	if(inverse_square_matrix(A, B, M)){
		printf("Inversion of matrix A is: \nB = \n");
		print_square_matrix(B, M);
	} else {
		printf("Not exist the inversion of matrix A.\n");
	}

	free(A);
	free(B);

}