#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define  M       20
#define  Time    10
#define  dt      0.01
#define  dx      0.1
#define  D       0.1


void DisplayArray(float *T, int size)
{
  int i;
  for(i=0;i<size;i++)
    printf("  %.2f",*(T+i));
  printf("\n");  
}
//=========================
void KhoiTao(float *T)
{
  int i;
  for (  i = 0 ; i < M ; i++ )
     *(T+i) = 25.0;
}
//=========================
void DHB2(float *Ts, float Tl, float Tr, float *dTs ,int ms) {
  int i;
  float c, l, r;
  for (i = 0 ; i < ms ; i++ ) {
    c = *(Ts + i);
    l = (i == 0)        ? Tl   : *(Ts + i - 1);
    r = (i == ms - 1)   ? Tr   : *(Ts + i + 1);
    *(dTs + i) = D * (l - 2 * c + r) / (dx * dx);
  }
}
//=========================
int main(int argc, char *argv[])
{
  int NP,ID, Ntime;
  Ntime = Time / dt;
  MPI_Init(&argc, &argv);
  MPI_Status Trangthai;
  MPI_Comm_size(MPI_COMM_WORLD,&NP);
  MPI_Comm_rank(MPI_COMM_WORLD,&ID);
//
  int i,t;
  float *T,*dT;
  T  = (float *) malloc ((M)*sizeof(float));
  dT = (float *) malloc ((M)*sizeof(float));
//  Step 1:
  if (ID==0) KhoiTao(T);
//  Step 2:
  int Mc;
  float *Tc,*dTc;
  Mc = M/NP;
  Tc  = (float *) malloc ((Mc)*sizeof(float));
  dTc = (float *) malloc ((Mc)*sizeof(float));
//  Step 3:
  MPI_Scatter(T,Mc,MPI_FLOAT,Tc,Mc,MPI_FLOAT,0,MPI_COMM_WORLD);
//  Step 4
  float Tl,Tr;
for (t=0;t<Ntime;t++)
    {
//  4.1.a
  if (ID == 0){
    Tl = 100;
    MPI_Send (Tc + Mc - 1, 1, MPI_FLOAT, ID + 1, ID, MPI_COMM_WORLD);
  } else if (ID == NP - 1) {
    MPI_Recv (&Tl, 1, MPI_FLOAT, ID - 1, ID - 1, MPI_COMM_WORLD, &Trangthai);
  } else {
    MPI_Send (Tc + Mc - 1, 1, MPI_FLOAT, ID + 1, ID, MPI_COMM_WORLD);
    MPI_Recv (&Tl, 1, MPI_FLOAT, ID - 1, ID - 1, MPI_COMM_WORLD, &Trangthai);
  }
//  4.1.b
  if (ID == NP - 1){
    Tr = 25;
    MPI_Send (Tc, 1, MPI_FLOAT, ID - 1, ID, MPI_COMM_WORLD);
  } else if (ID == 0) {
    MPI_Recv (&Tr, 1, MPI_FLOAT, ID + 1, ID + 1, MPI_COMM_WORLD, &Trangthai);
  } else {
    MPI_Send (Tc, 1, MPI_FLOAT, ID - 1, ID, MPI_COMM_WORLD);
    MPI_Recv (&Tr, 1, MPI_FLOAT, ID + 1, ID + 1, MPI_COMM_WORLD, &Trangthai);
  }
//  4.2 DHB2(float *Ts, float Tl, float Tr, float *dTs ,int ms)
    DHB2(Tc, Tl, Tr, dTc, Mc);
    for (  i = 0 ; i < Mc ; i++ )
        *(Tc+i) = *(Tc+i) + dt*(*(dTc+i));
    }
//  Step 5:
  MPI_Gather(Tc,Mc,MPI_FLOAT,T,Mc,MPI_FLOAT,0,MPI_COMM_WORLD);
//  In Ket Qua
  if (ID==0)
    DisplayArray(T, M);
return 0;
}


