#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <omp.h>

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

void FD(float *Phi_current,float *dPhi, int start, int end)
{
  int i;
  float c,l,r;
  for (i = start ; i < end ; i++){
    c = *(Phi_current+i);
    l = (i==0)    ? - *(Phi_current+i+1) : *(Phi_current+i-1);
    //left neighbor = -r in order to to dPhi=0
    r = (i==m-1) ? - *(Phi_current+i-1) : *(Phi_current+i+1);
    //right neighbor = -l in order to dPhi=0
    *(dPhi+i) = l - 2*c + r;
  }
}
//=========================

int main()
{
  int i;
  float dx,t,tau;
  t = 0.0;
  float *Phi_old,*Phi_current,*Phi_new,*dPhi;

  Phi_old     = (float *) malloc (m*sizeof(float));
  Phi_current = (float *) malloc (m*sizeof(float));
  Phi_new     = (float *) malloc (m*sizeof(float));
  dPhi        = (float *) malloc (m*sizeof(float));
  KhoiTao(Phi_old,Phi_current);

  Write2File(Phi_current,m,1);

  printf("Gia tri khoi tao:\n");
  DisplayMatrix(Phi_old, m, 1);

  dx = 1.0/(m-1);
  tau = C*dt/dx;

  // Parallel bro
  int NT, Mc, ID, start, stop;

  omp_set_num_threads(4);  
  #pragma omp parallel private(ID,start,stop,i, t, Mc)
  {
      ID = omp_get_thread_num();
      NT = omp_get_num_threads();
      Mc = m/NT;
      start = ID*Mc;
      stop  = start + Mc;

      while (t<=T)
      {
        FD(Phi_current, dPhi, start, stop);
        #pragma omp barrier // synchronise


        for (i = start ; i < stop ; i++)
          *(Phi_new+i) = 2*(*(Phi_current+i)) - *(Phi_old+i) + tau*tau*(*(dPhi+i));


        for (i = start ; i < stop ; i++){
          *(Phi_old+i)      = *(Phi_current+i);
          *(Phi_current+i)  = *(Phi_new+i);
        }

        
        t=t+dt;

        #pragma omp barrier // synchronise for writing file
        #pragma omp single
        {
          Write2File(Phi_current,m,1);
        }
        // auto pragma omp barrier after omp single

      }

  }

  printf("Gia tri cuoi cung:\n");
  DisplayMatrix(Phi_current, m, 1);
  return 0;
}

