#include <stdio.h>
#include <stdlib.h>


int main()
{
	float income;
	float tax;
	// Input 
	while(1)
	{
		printf("Input your income: ");
		scanf("%f", &income);

		if (income < 0.0){
			printf("Invalid input value, your income %.2f must be positive.\n\n",
				income);
		} else {

			if (income <= 1000.0){
				tax = 0.0;
			}
			else if (income <= 2000){
				tax = (income - 1000.0)*0.05;
			}
			else if (income <= 4000){
				tax = (income - 2000.0)*0.1 + 50;
			}
			else {
				tax = (income - 4000.0)*0.2 + 250;
			}

			printf("If the income is %.2f, then the personal income tax to be paid is %.2f.\n\n", 
				income, tax);

			break;
		}

	}
}