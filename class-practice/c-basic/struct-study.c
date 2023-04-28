#include <stdio.h>

struct ThongTinSV{
	int ID;
	char Name[10];
	float DiemQT, DiemCK;
	char XepLoai; 
};

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}



int main()
{
	struct ThongTinSV DSAIK65[3];
	int i;
	for (i=0; i<3;i++){
		printf("Ten SV %d: ", i);

		fgets(DSAIK65[i].Name, 10, stdin);



		printf("Ma SV %d: ", i);
		scanf("%d", &DSAIK65[i].ID);

		printf("DQT %d: ", i);
		scanf("%f", &DSAIK65[i].DiemQT);

		printf("DCK %d: ", i);
		scanf("%f", &DSAIK65[i].DiemCK);

		clean_stdin();


	}

	return 0;
}