#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define  C       1
#define  m       20
#define  T       5
#define  dt      0.01
//=========================

void DisplayMatrix(float *A, int row,  int col)
{
  int i,j;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++) 
      printf("  %f",*(A+i*col+j));
    printf("\n");
  }
}

//=========================
void Write2File(float *A, int row,  int col)
{
  FILE *result=fopen("ViberStringC1.txt", "a");
  int i,j;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){ 
      fprintf(result, "%lf\t", *(A+i*col+j));
    }
    fprintf(result, "\n");
  }

  fprintf(result, "\n");
  fclose(result);
}
//=========================

void KhoiTao(float *Phi_old,float *Phi_current)
{
  int i;
  float dx,X;
  dx = 1.0/(m-1);
  for (i = 0 ; i < m ; i++){
    X = i*dx;
    // Phi_old is the same as Phi_current
    *(Phi_old+i)= sin(2.0*M_PI*X);
    *(Phi_current+i) = *(Phi_old+i);
  }
}
//=========================

void FD(float *Phi_current,float *dPhi, float Tl, float Tr, int mc)
{
  int i;
  float c,l,r;
  for (i = 0 ; i < mc ; i++){
    c = *(Phi_current+i);
    l = (i==0)    ? Tl : *(Phi_current+i-1);
    //left neighbor = -r in order to to dPhi=0
    r = (i==mc-1) ? Tr : *(Phi_current+i+1);
    //right neighbor = -l in order to dPhi=0
    *(dPhi+i) = l - 2*c + r;
  }
}
//=========================

int main(int argc, char *argv[])
{
  int NP, ID, i;

  MPI_Init(&argc, &argv);
  MPI_Status Trangthai;
  MPI_Comm_size(MPI_COMM_WORLD,&NP);
  MPI_Comm_rank(MPI_COMM_WORLD,&ID);  

  float *Phi_old,*Phi_current,*Phi_new,*dPhi;
  float dx,t,tau;

  t = 0.0;
  dx = 1.0/(m-1);
  tau = C*dt/dx;



  Phi_old     = (float *) malloc (m*sizeof(float));
  Phi_current = (float *) malloc (m*sizeof(float));
  Phi_new     = (float *) malloc (m*sizeof(float));
  dPhi        = (float *) malloc (m*sizeof(float));

  // Step 1
  if (ID==0){
    KhoiTao(Phi_old,Phi_current);
    printf("Gia tri ban dau:\n");
    DisplayMatrix(Phi_current, m, 1);
  } 
  // Step 2
  int mc;
  float *Phi_old_c,*Phi_current_c,*Phi_new_c,*dPhi_c;
  mc = m / NP;

  Phi_old_c     = (float *) malloc (mc*sizeof(float));
  Phi_current_c = (float *) malloc (mc*sizeof(float));
  Phi_new_c     = (float *) malloc (mc*sizeof(float));
  dPhi_c        = (float *) malloc (mc*sizeof(float));

  // Step 3
  MPI_Scatter(Phi_old,mc,MPI_FLOAT,Phi_old_c,mc,MPI_FLOAT,0,MPI_COMM_WORLD);
  MPI_Scatter(Phi_current,mc,MPI_FLOAT,Phi_current_c,mc,MPI_FLOAT,0,MPI_COMM_WORLD);
  MPI_Scatter(Phi_new,mc,MPI_FLOAT,Phi_new_c,mc,MPI_FLOAT,0,MPI_COMM_WORLD);

  // Step 4

  float Tl, Tr; 


  while (t<=T)
  {

    // 4.1.a
    if (ID==0){
      Tl = -*(Phi_current_c+1);
      MPI_Send (Phi_current_c + mc - 1, 1, MPI_FLOAT, ID + 1, ID, MPI_COMM_WORLD);
    }
    else if (ID == NP - 1) {
      MPI_Recv (&Tl, 1, MPI_FLOAT, ID - 1, ID - 1, MPI_COMM_WORLD, &Trangthai);
    }
    else {
      MPI_Send (Phi_current_c + mc - 1, 1, MPI_FLOAT, ID + 1, ID, MPI_COMM_WORLD);
      MPI_Recv (&Tl, 1, MPI_FLOAT, ID - 1, ID - 1, MPI_COMM_WORLD, &Trangthai);
    }

    // 4.1.b
    if (ID == NP - 1){
      Tr = -*(Phi_current_c+mc-2);
      MPI_Send (Phi_current_c, 1, MPI_FLOAT, ID - 1, ID, MPI_COMM_WORLD);
    } else if (ID == 0) {
      MPI_Recv (&Tr, 1, MPI_FLOAT, ID + 1, ID + 1, MPI_COMM_WORLD, &Trangthai);
    } else {
      MPI_Send (Phi_current_c, 1, MPI_FLOAT, ID - 1, ID, MPI_COMM_WORLD);
      MPI_Recv (&Tr, 1, MPI_FLOAT, ID + 1, ID + 1, MPI_COMM_WORLD, &Trangthai);
    }

    // 4.2 
    FD(Phi_current_c, dPhi_c, Tl, Tr, mc);
    for (i = 0 ; i < mc ; i++)
      *(Phi_new_c+i) = 2*(*(Phi_current_c+i)) - *(Phi_old_c+i) + tau*tau*(*(dPhi_c+i));

    for (i = 0 ; i < mc ; i++){
      *(Phi_old_c+i)      = *(Phi_current_c+i);
      *(Phi_current_c+i)  = *(Phi_new_c+i);
    }

    t=t+dt;
  }

  // Step 5:
  MPI_Gather(Phi_old_c,mc,MPI_FLOAT,Phi_old,mc,MPI_FLOAT,0,MPI_COMM_WORLD);
  MPI_Gather(Phi_current_c,mc,MPI_FLOAT,Phi_current,mc,MPI_FLOAT,0,MPI_COMM_WORLD);
  MPI_Gather(Phi_new_c,mc,MPI_FLOAT,Phi_new,mc,MPI_FLOAT,0,MPI_COMM_WORLD);


  if(ID==0){
    printf("Gia tri cuoi cung:\n");
    DisplayMatrix(Phi_current, m, 1);
  }

  MPI_Finalize();

  return 0;
}

