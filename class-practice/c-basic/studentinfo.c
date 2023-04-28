#include <stdio.h>
#include <math.h>

int main()
{
	char tensv[30], gioitinh;
	int tuoisv;
	float diemgk, diemck, diemtk;
	puts("Nhap ten SV: ");
	fgets(tensv, sizeof(tensv), stdin);
	fflush(stdin);

	puts("Nhap gioi tinh SV:");
	scanf("%c", &gioitinh);

	puts("Nhap tuoi sv:");
	scanf("%d", &tuoisv);

	printf("%f", sqrt(2));

	puts("Nhap diem sv:");
	scanf("%f %f", &diemgk, &diemck);

	diemtk = 0.4 * diemgk + 0.6*diemck;

	printf("Ban %s, gioi tinh %c, %d tuoi, diem la %f\n", 
		tensv, gioitinh, tuoisv, diemtk);


}