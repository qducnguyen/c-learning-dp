#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>


#define nx 51 
#define ny 51
#define nt 100
#define nit 50 
#define c 1.0
#define xmax 2.0
#define ymax 2.0 
#define rho 1.0 
#define nu 0.1
#define dt 0.001


void save_results(double *u, double *v, double *p, char *filename){
	//  
	FILE *file = fopen(filename, "w");
	int i,j;
	for (i = 0; i < ny; i++){
		for (j = 0; j < nx; j++){
			// 73 pecision ..
			fprintf(file, "%.73lf ", *(u + i*nx + j));
		}
		fprintf(file, "\n");
	}

	fprintf(file, "----------------\n");

	for (i = 0; i < ny; i++){
		for (j = 0; j < nx; j++){
			// 73 pecision ..
			fprintf(file, "%.73lf ", *(v + i*nx + j));
		}
		fprintf(file, "\n");
	}
	fprintf(file, "----------------\n");

	for (i = 0; i < ny; i++){
		for (j = 0; j < nx; j++){
			// 73 pecision ..
			fprintf(file, "%.73lf ", *(p + i*nx + j));
		}
		fprintf(file, "\n");
	}
	fprintf(file, "----------------\n");


	fclose(file);
}

void print_array(double *arr){
	printf("\n\n");	
	int i, j;
	for (i = 0; i < ny; i++){
		for (j = 0; j < nx; j++){
			printf("%e ", *(arr + i * nx + j));
		}
		printf("\n\n");
	}
}


void init(double *u, double *v, double *p, double *b){
	int i, j;
	for (i = 0; i < ny; i++){
		for (j = 0; j < nx; j++){
			*(u + i * nx + j) = 0.0;
			*(v + i * nx + j) = 0.0;
			*(p + i * nx + j) = 0.0;
			*(b + i * nx + j) = 0.0;
		}
	}
}


void build_up_b(double *b, double *u, double *v, double dx, double dy){
	int i, j;
	for (i = 1; i < ny - 1; i++){
		for (j = 1; j < nx - 1; j++){
			*(b + i * nx + j) = rho * (1 / dt *
				((*(u + i * nx + j + 1) - *(u + i * nx + j - 1)) / (2*dx)
				+(*(v + (i+1)*nx + j) - *(v + (i-1)*nx +j)) / (2*dy)) -
			pow((*(u + i * nx + j + 1) - *(u + i*nx + j-1)) / (2*dx), 2) -
			2 * ((*(u + (i+1)*nx + j) - *(u + (i-1)*nx +j)) / (2*dy) *
			(*(v + i * nx + j + 1) - *(v + i * nx + j - 1)) / (2*dx)) - 
			pow((*(v + (i+1)*nx + j) - *(v + (i-1)*nx +j)) / (2*dy), 2));
		}
	}
}

void pressure_poisson(double *p, double *b, double dx, double dy){
	int it, i, j;
	

	for (it = 0; it < nit; it++){
		// Mem copy
		size_t size = nx * ny * sizeof(double);
		double *pn = (double *) malloc(size);
		memcpy(pn, p, size);

		// Calculate	

		for (i = 1; i < ny - 1; i++){
			for (j = 1; j < nx - 1; j++){
				*(p + i*nx + j) = ((*(pn + i*nx + j + 1) + *(pn + i * nx + j -1)) * dy*dy  + 
									(*(pn + (i+1)*nx + j) + *(pn + (i-1)*nx + j)) * dx*dx) /
									(2 * (dx*dx + dy*dy))- 
									dx*dx*dy*dy / (2 * (dx*dx + dy*dy)) * *(b + i*nx +j);
			}
		}

		// dp/dx = 0 at x = xmax
		for (i = 0; i < ny; i++){
			*(p + i*nx + nx - 1) = *(p + i*nx + nx - 2);
		}

		// dp/dy = 0 at y = 0
		for (j = 0; j < nx; j++){
			*(p + j) = *(p + nx + j);
		}

		// dp/dx = 0 at x = 0

		for (i = 0; i < ny; i++){
			*(p + i*nx ) = *(p + i*nx + 1);
		}

		// p = 0 at y = 2
		for (j = 0; j < nx; j++){
			*(p + (ny-1)*nx + j ) = 0;
		}


		free(pn);
	}
}


void cavity_flow(double *u, double *v, double *p, double *b, double dx, double dy){

	int n, i, j;


	for(n =0; n < nt; n++){
		// Mem copy
		size_t size_u = nx * ny * sizeof(double);
		double *un = (double *) malloc(size_u);
		memcpy(un, u, size_u);

		size_t size_v = nx * ny * sizeof(double);
		double *vn = (double *) malloc(size_v);
		memcpy(vn, v, size_v);

		build_up_b(b, u, v, dx, dy);
		pressure_poisson(p, b, dx, dy);


		for (i = 1; i < ny - 1; i++){
			for (j = 1; j < nx - 1;j++){
				*(u + i*nx + j) = *(un + i*nx + j) - 
								  *(un + i*nx + j) * dt / dx  * 
								  (*(un + i*nx +j) - *(un + i*nx + j-1)) -
								  *(vn + i*nx +j) * dt / dy *
								  (*(un + i*nx +j) - *(un + (i-1)*nx + j)) - 
								  dt / (2 * rho * dx) * (*(p + i*nx + j+1) - *(p + i*nx +j-1)) +
								  nu * (dt / (dx*dx) *
								  	(*(un + i*nx +j+1) - 2 * *(un + i*nx +j) + *(un + i*nx + j-1)) +
								  	dt/ (dy*dy) *
								  	(*(un + (i+1)*nx +j) - 2 * *(un + i*nx +j) + *(un + (i-1)*nx + j)));

				*(v + i*nx + j) = *(vn + i*nx + j) - 
								  *(un + i*nx + j) * dt / dx  * 
								  (*(vn + i*nx +j) - *(vn + i*nx + j-1)) -
								  *(vn + i*nx +j) * dt / dy *
								  (*(vn + i*nx +j) - *(vn + (i-1)*nx + j)) - 
								  dt / (2 * rho * dy) * (*(p + (i+1)*nx + j) - *(p + (i-1)*nx +j)) +
								  nu * (dt / (dx*dx) *
								  	(*(vn + i*nx +j+1) - 2 * *(vn + i*nx +j) + *(vn + i*nx + j-1)) +
								  	dt/ (dy*dy) *
								  	(*(vn + (i+1)*nx +j) - 2 * *(vn + i*nx +j) + *(vn + (i-1)*nx + j)));
			}
		}

		for (i = 0; i < ny; i++){
			*(u + i * nx) = 0;
			*(u + i * nx + nx - 1) = 0;
			*(v + i * nx) = 0;
			*(v + i * nx + nx - 1) = 0;
		}



		for (j = 0; j < nx; j++){
			*(u + j) = 0;
			*(u + (ny-1)*nx + j) = 1; 	// set velocity on cavity lid equal to 1	
			*(v + j) = 0;
			*(v + (ny-1)*nx + j) = 0; 

		}


		free(un);
		free(vn);
	}
}




int main(){

	char* result_file_name = "flow_results.txt";

	int i, j, t;
	double *u, *v, *p, *b;
	double dx = xmax / (nx-1);
	double dy = ymax / (ny-1);

	u = (double *) malloc((nx * ny) * sizeof(double));
	v = (double *) malloc((nx * ny) * sizeof(double));
	p = (double *) malloc((nx * ny) * sizeof(double));
	b = (double *) malloc((nx * ny) * sizeof(double));

	init(u, v, p ,b);

	cavity_flow(u, v, p, b, dx, dy);

	save_results(u, v, p, result_file_name);

	free(u);
	free(v);
	free(p);
	free(b);

	return 0;
}