#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mpi.h>
#include <math.h>
#include <sys/time.h>
// Nhap cac kich thuoc cua ma tran
#define  m       8
#define  n       8
#define  p       4
//==================================
void DisplayMatrix(int *A, int row,  int col){
  int i,j;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++) printf("%d\t",*(A+i*col+j));
    printf("\n");
  }
}
//==================================
int main(int argc, char *argv[])
{
  int NP, rank, mc;
  int i, j, k, sum = 0.0;
  MPI_Status status;
//==================================
// Khai bao ma tran A, B, C
// va ma tran con Ac, Bc, CC
  int *A, *B, *C, *Ac, *Bc, *Cc;
  A = (int *) malloc ((m*n)*sizeof(int));
  B = (int *) malloc ((n*p)*sizeof(int));
  C = (int *) malloc ((m*p)*sizeof(int));
//==================================
// Khoi tao MPI
  MPI_Init(&argc,&argv);
//==================================
// Tinh so process: NP; gan ID cho tung process:rank  
  MPI_Comm_size(MPI_COMM_WORLD,&NP);    
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
//==================================
// Tinh kich thuoc cua cac ma tran con
  mc = m/NP;
// Cap phat bo nho cho cac ma tran con
  Ac = (int *) malloc ((mc*n)*sizeof(int));
  Bc = (int *) malloc ((n*p)*sizeof(int)); // the same matrix B
  Cc = (int *) malloc ((mc*p)*sizeof(int));
//==================================
// Khoi Tao Du Lieu (Ma tran A, B) tai Core 0
  if (rank==0) {
  //Ma tran A la ma tran Don vi (I)
   for (  i = 0 ; i < m ; i++ )
    for ( j = 0 ; j < n ; j++ ){
      if (i==j) 
        *(A+i*n+j) = 1.0;
      else
        *(A+i*n+j) = 0.0;
    }
    printf("The matrix A:\n");
    DisplayMatrix(A, m, n);
  //Ma tran B
   for (  i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < p ; j++ ){
      *(B+i*p+j) = 1.0*(i*p+j);
    }
    printf("The matrix B\n");
    DisplayMatrix(B, n, p);
  }
//==================================
// Gui Ma tran A tu Core 0 den tat ca cac Core
   MPI_Scatter(A,mc*n,MPI_INT,
              Ac,mc*n,MPI_INT,0,
              MPI_COMM_WORLD);
  //printf( "Ma tran Ac tai core %d is:\n", rank);
  //DisplayMatrix(Ac, mc, n);
//==================================
// Gui Ma tran B tu Core 0 den tat ca cac Core
  if (rank==0)
    for ( i = 0 ; i < n ; i++ )
      for ( j = 0 ; j < p ; j++ )
        *(Bc+i*p+j) = *(B+i*p+j);
  MPI_Bcast(Bc,n*p,MPI_INT,0,MPI_COMM_WORLD);
  //printf( "Ma tran Bc tai core %d is:\n", rank);
  //DisplayMatrix(Bc, n, p);
//==================================  
 // Nhan Ma Tran: Ac x Bc = Cc
  for ( i = 0 ; i < mc ; i++ )
    {
      for ( j = 0 ; j < p ; j++ )
      {
        for ( k = 0 ; k < n ; k++ )
        {
          sum = sum + (*(Ac + i*n + k)) * (*(Bc + k*p + j));
        } 
        *(Cc + i*p + j) = sum;
        sum = 0.0;
      }
    }
  //printf( "Ma tran Cc tai core %d is:\n", rank);
  //DisplayMatrix(Cc, mc, p);
//==================================
// Gui Ma tran C tu tat ca cac Core ve Core 0
  MPI_Gather(Cc,mc*p,MPI_INT,
             C,mc*p,MPI_INT,0,
             MPI_COMM_WORLD);
// In Ket Qua Tai Core 0
  if (rank==0)
    {
      printf( "Ma tran C:\n");
      DisplayMatrix(C, m, p);
    }
//==================================
  MPI_Finalize();
  return 0;
}

