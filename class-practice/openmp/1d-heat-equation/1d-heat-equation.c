#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TEMP	25.0
#define TEMP_0	100.0
#define	M 		20
#define Time	10
#define dt		0.01
#define dx		0.1
#define D 		0.1


void DisplayArray(float *T, int size){
	int i;
	for(i=0;i<size;i++){
		printf("	%.2f", *(T+i));
	}
	printf("\n");
}  

FILE* Open2WriteFile(char *filename){
	return fopen(filename, "w+");
}

void Write2File(FILE* file, int start_idx ,float *T, int size){

	int i;	

	fprintf(file, "-----------------------------\n");
	if (start_idx != -1){
		fprintf(file, "Step %d\n\n" , start_idx);
	}

	for(i=0;i<size;i++) {
		fprintf(file, "%lf", *(T+i));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

}

void Close2WriteFile(FILE* file){
	fclose(file);
}





void KhoiTao(float *T){
  	int i;
 	for (i = 0 ; i < M ; i++)
     *(T+i) = TEMP;

}


void DHB2(float *T, float *dT, int Dau, int Cuoi){
	int i;
	float c,l,r;
	for (i = Dau ; i < Cuoi ; i++ )
	    {
	      c = *(T+i);
	      l = (i==0)   ? TEMP_0 : *(T+(i-1));
	      r = (i==M-1) ? TEMP  : *(T+(i+1));
	      *(dT+i) = D*(r-2*c+l)/(dx*dx);
	    }
}


int main(){
	int i,t, Ntime;
	float *T,*dT;
	T  = (float *) malloc ((M)*sizeof(float));
	dT = (float *) malloc ((M)*sizeof(float));

	KhoiTao(T);
	FILE *file = Open2WriteFile("results.txt");

	printf("Gia tri khoi tao:\n");
	DisplayArray(T, M);
	Write2File(file, -1 ,T,M);

	Ntime = Time/dt;

	for (t=0;t<Ntime;t++) {
	    DHB2(T, dT, 0, M);

	    for ( i = 0 ; i < M ; i++){
	          *(T+i) = *(T+i) + *(dT+i) * dt;
	      }

	    Write2File(file, t, T, M);
	}

	printf("Result of C:\n");
	DisplayArray(T, M);

	Close2WriteFile(file);
	return 0;
}
