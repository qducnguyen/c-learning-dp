#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0){
		int *A, i;
		A = (int *)malloc(10*sizeof(int));
		for (i=0;i < 10;i++){
			*(A+i) = i+1;
		}
		MPI_Send(A,
			10,
			MPI_INT,
			1,
			2023,
			MPI_COMM_WORLD
			);

	}
	else if(rank == 1){
		int *B,*C, i;
		B = (int *)malloc(10*sizeof(int));
		C = (int *)malloc(10*sizeof(int));	

		MPI_Recv(B,
			10,
			MPI_INT,
			0,
			2023,
			MPI_COMM_WORLD,
			MPI_STATUS_IGNORE
			);

		for(i=0; i<10;i++){
			*(C+i)=  2 * *(B+i);
		}

		printf("I'm rank %d in the total of %d CPU\n", rank, size);
		for(i=0; i<10;i++){
			printf("%d ", *(C+i));
		}

		printf("\n");
	}
	
	MPI_Finalize();
	return 0;
}