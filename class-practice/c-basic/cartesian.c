#include <math.h>
#include <stdio.h>


float distance_two_point(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

int main()
{	
	float x1, x2, y1, y2, result;
	printf("Input the first point: ");
	scanf("%f %f", &x1, &y1);
	printf("Input the second point: ");
	scanf("%f %f", &x2, &y2);

	result = distance_two_point(x1, y1, x2, y2);

	printf("The distance between two points is: %f\n", result);

	return 0;
}	