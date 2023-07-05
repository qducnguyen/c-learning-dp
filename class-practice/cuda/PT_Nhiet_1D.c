#include <stdio.h>
#include <malloc.h>
#define  M       32
#define  Ntime   100
#define  dt      0.01
#define  dx      0.1
#define  D       0.1
//=========================
void KhoiTao(float *T){
  int i;
  for (  i = 0 ; i < M ; i++ )
     *(T+i) = 25.0;
}
//=========================
void DHB2(float *T, float *dT){
    int i;
    float c,l,r;
    for (  i = 0 ; i < M ; i++ ) {
          c = *(T+i);
          l = (i==0)   ? 100.0 : *(T+(i-1));
          r = (i==M-1) ? 25.0  : *(T+(i+1));
          *(dT+i) = D*(r-2*c+l)/(dx*dx);
        }
}
//=========================
int main(){
    int i,t;
    float *T,*dT;
    T  = (float *) malloc ((M)*sizeof(float));
    dT = (float *) malloc ((M)*sizeof(float));
    KhoiTao(T);
    for (t=0;t<Ntime;t++) {
          DHB2(T, dT);
          for ( i = 0 ; i < M ; i++ )
              *(T+i) = *(T+i) + dt*(*(dT+i));
        }
    for (  i = 0 ; i < M ; i++ ) printf("%f \n",*(T+i));
    return 0;
}


