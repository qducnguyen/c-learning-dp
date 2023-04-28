#include <stdarg.h>
#include <stdio.h>

void print_ints(int args, ...){
	va_list ap;
	va_start(ap, args);

	int i;

	for (i =0; i< args; i++){
		printf("argument: %i\n", va_arg(ap, int));
	}

	va_end(ap)
;}




int main()
{

	print_ints(5, 23, -32, 4, 5 ,6);

}