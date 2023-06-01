#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 20

int main(int argc, char *argv[])
{
	// Break into many part

	int rank, size;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int break_part_size = ARRAY_SIZE / size;


	if (rank == 0){
		// Init A, B, C 
		int *A,*B,*C, i;
		A = (int *)malloc(ARRAY_SIZE*sizeof(int));
		B = (int *)malloc(ARRAY_SIZE*sizeof(int));
		C = (int *)malloc(ARRAY_SIZE*sizeof(int));

		for (i=0;i < ARRAY_SIZE;i++){
			*(A+i) = i+1;
			*(B+i) = 2*(i+1);
		}

		for (i=0; i < break_part_size;i++ ){
			*(C+i)  = *(A+i) + *(B+i);
		}

		
		// Send all except last piece
		for (i=1; i<size-1; i++){
			MPI_Send(A + break_part_size * i,
					 break_part_size,
					 MPI_INT,
					 i,
					 2023,
					 MPI_COMM_WORLD
					);

			MPI_Send(B + break_part_size * i,
					 break_part_size,
					 MPI_INT,
					 i,
					 2024,
					 MPI_COMM_WORLD
					);
		}
  
		// Send last piece
		MPI_Send(A + break_part_size * (size - 1),
				 ARRAY_SIZE - break_part_size * (size - 1), 
				 MPI_INT,
				 size-1,
				 2023,
				 MPI_COMM_WORLD);


		MPI_Send(B + break_part_size * (size - 1),
				 ARRAY_SIZE - break_part_size * (size - 1), 
				 MPI_INT,
				 size-1,
				 2024,
				 MPI_COMM_WORLD);



		for (i=1; i<size-1; i++){
			MPI_Recv(C + break_part_size * i,
					 break_part_size,
					 MPI_INT,
					 i,
					 0,
					 MPI_COMM_WORLD,
					 MPI_STATUS_IGNORE
					);

		}

		MPI_Recv(C + break_part_size * (size - 1),
				 ARRAY_SIZE - break_part_size * (size - 1), 
				 MPI_INT,
				 size-1,
				 0,
				 MPI_COMM_WORLD,
				 MPI_STATUS_IGNORE);

		
		// print C
		printf("From %d rank, C =\n", rank);
		for (i=0; i<ARRAY_SIZE;i++){
			printf("%d ", *(C+i));
		}
		printf("\n");
	}




	else {
		int *A, *B,*C, i, size_part;
		if (rank == size-1) {
			size_part =  ARRAY_SIZE - break_part_size * (size - 1);
		}

		else{
			size_part = break_part_size;
		}

		A = (int *)malloc(size_part*sizeof(int));
		B = (int *)malloc(size_part*sizeof(int));
		C = (int *)malloc(size_part*sizeof(int));

		

		MPI_Recv(A,
			size_part,
			MPI_INT,
			0,
			2023,
			MPI_COMM_WORLD,
			MPI_STATUS_IGNORE
			);

		MPI_Recv(B,
			size_part,
			MPI_INT,
			0,
			2024,
			MPI_COMM_WORLD,
			MPI_STATUS_IGNORE
			);

		for(i=0; i<size_part;i++){
			*(C+i)=  *(A+i) + *(B+i);
		}

		MPI_Send(C,
			size_part,
			MPI_INT,
			0,
			0,
			MPI_COMM_WORLD
			);

	}

	MPI_Finalize();
	return 0;
}