#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int main(int argc, char**argv){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status stat;
	int s[MAX] = {0,1 ,2, 3, 4, 5, 6, 7, 8, 9};
	int r[MAX];



	MPI_Recv(r, 
			MAX, 
			MPI_INT,
			1-rank,
			rank,
			MPI_COMM_WORLD,
			&stat);


	MPI_Send(s,
			MAX,
			MPI_INT,
			1-rank,
			1-rank,
			MPI_COMM_WORLD);



	// Dead f*cklock but not away round
	
	printf("Process %d received: \n", rank);

	MPI_Finalize();
	return 0; 
}