#include <stdio.h>

int main()
{
	char tensv[30], gradename ;
	float diemgk, diemck, diemtk;
	puts("Nhap ten SV: ");
	fgets(tensv, sizeof(tensv), stdin);
	fflush(stdin);

	puts("Nhap diem sv:");
	scanf("%f %f", &diemgk, &diemck);

	diemtk = 0.4*diemgk + 0.6*diemck;


	if ((diemgk < 3) || (diemck < 3))
		gradename = 'F';
	else 
		if (diemtk < 4)
			gradename = 'F';
		else if (diemtk < 7)
			gradename = 'D';
		else if (diemtk < 8.5)
			gradename = 'B';
		else 
			gradename = 'A';

	printf("Ban %s xep loai %c\n", tensv, gradename);

}