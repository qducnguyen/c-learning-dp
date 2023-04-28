#include <stdio.h>

static long num_steps = 100000;
double step;

int main()
{

	// Serial version

	// int i; 
	// double x, pi, sum = 0.0;

	// step = 1.0 / (double)num_steps;

	// for (i=0; i< num_steps;i++){
	// 	x = (i+0.5) * step;
	// 	sum += 4.0 / (1.0 + x*x);
	// }

	// pi = step * sum;


	// Ex2

	int num_threads = 4;
	omp_set_num_threads(num_threads);

	int i;
	double x, pi, sum = 0.0;

	step = 1.0 / (double)num_steps;


	#pragma omp parallel private(x, i)
	{


	for (i=0; i< num_steps;i++){
		x = (i+0.5) * step;
		sum += 4.0 / (1.0 + x*x);
	}
	}	

	pi = step * sum;

	printf("\n%lf\n", pi);
}