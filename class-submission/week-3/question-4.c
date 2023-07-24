// Only input polynominal mathematical formular 


#include <math.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
	int pol_num;
	float *poly; 
} function;


float polynominal_calculate(function *f, float x){
	int i;
	int pol_num = f->pol_num;
	float result = 0.0;
	for(i=0; i < pol_num +1; i++){
		result += *(f->poly + i) * pow(x, pol_num - i );
	}
	return result;
}



float Integral(function *f, float a, float b){

	float result = (polynominal_calculate(f, a) + polynominal_calculate(f, b)) / 2 * (b-a);


	return result;
}



int main()
{	
	int N;
	printf("Input the polynomial function ...\n");
	printf("Input degree of the function N: ");
	scanf("%d", &N);

	function f = {N, (float *)malloc((N+1)*sizeof(float))};

	int i;
	printf("Input the %d coeffiecient of the function: ", N + 1);
	for (i=0; i<N+1;i++){
		scanf("%f", f.poly + i);
	}

	float a, b;
	printf("Input lower bound a: ");
	scanf("%f", &a);

	printf("Input upper bound b: ");
	scanf("%f", &b);

	float result = Integral(&f, a, b);

	printf("\nResult of the integral is: %f\n", result);


}

