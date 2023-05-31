#include <stdio.h>
#include <malloc.h>
#include <mpi.h>
#define  m       20
int main(int argc, char *argv[])
{
  int i, k, ms, NP, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &NP);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Status status;
  ms = m/NP;
  int *As, *Bs, *Cs;
  As = (int *) malloc (ms*sizeof(int));
  Bs = (int *) malloc (ms*sizeof(int));
  Cs = (int *) malloc (ms*sizeof(int));
  int *A, *B, *C;
  A = (int *) malloc (m*sizeof(int));
  B = (int *) malloc (m*sizeof(int));
  C = (int *) malloc (m*sizeof(int));
// Step 1: Input Data
  if (rank==0) 
  	for (  i = 0 ; i < m ; i++ ) {
      *(A+i) = i;
      *(B+i) = 2*i;
  	}
// Step 2: Distribute Input from Rank 0 to All other Rank
  MPI_Scatter(A, ms, MPI_INT, As, ms, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(B, ms, MPI_INT, Bs, ms, MPI_INT, 0, MPI_COMM_WORLD);
// Step 3: Calculation on all Rank
  for ( i = 0 ; i < ms ; i++ )
     *(Cs + i) = *(As + i) + *(Bs + i);
// Step 4: Gather from all Rank and storen in Rank 0
  MPI_Gather(Cs, ms, MPI_INT, C, ms, MPI_INT, 0, MPI_COMM_WORLD);
// Print Result
  if (rank==0){
     printf("C: "); for(i=0; i<m; i++ ) printf("%d  ",*(C+i));  printf("\n");
  } 
  MPI_Finalize();
  return 0;
}

