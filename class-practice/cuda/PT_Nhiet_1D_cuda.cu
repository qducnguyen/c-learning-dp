#include <stdio.h>
#include <malloc.h>
#include <cuda.h>
#define  M       32
#define  Ntime   100
#define  dt      0.01
#define  dx      0.1
#define  D       0.1

#define GridSize 2
#define BlockSize 8
#define ThreadSize M/(GridSize*BlockSize)

//=========================
void KhoiTao(float *T){

  int i;
  for (  i = 0 ; i < M ; i++ )
     *(T+i) = 25.0;
}
//=========================
__global__ void DHB2(float *T, float *dT){

    float c,l,r;
	int i,index, start, stop;
	index = blockIdx.x * blockDim.x + threadIdx.x;
    start = index*ThreadSize;
    stop  = start + ThreadSize;     
    for (i=start;i<stop;i++) {
      c = *(T+i);
      l = (i==0)   ? 100.0 : *(T+(i-1));
      r = (i==M-1) ? 25.0  : *(T+(i+1));
      *(dT+i) = D*(r-2*c+l)/(dx*dx);
      __syncthreads();
    }
}
__global__ void ODE(float *T,float *dT) 
{
	int i,index, start, stop;
	index = blockIdx.x * blockDim.x + threadIdx.x;
    start = index*ThreadSize;
    stop  = start + ThreadSize;
    for (i=start;i<stop;i++)
      *(T+i) = *(T+i) + dt*(*(dT+i));
	__syncthreads();
}
//=========================
int main(){

    int i,t;
    float *Tcpu,*dTcpu;
    Tcpu  = (float *) malloc ((M)*sizeof(float));
    dTcpu = (float *) malloc ((M)*sizeof(float));
    KhoiTao(Tcpu);
    
    // CUDA code

    //1. Delare and Allocate Mem on GPU
    float *Tgpu,*dTgpu;
    cudaMalloc((void**)&Tgpu ,M*sizeof(int));
    cudaMalloc((void**)&dTgpu,M*sizeof(int));

    //2. Copy Input from CPU to GPU
    cudaMemcpy(Tgpu,Tcpu,M*sizeof(int),cudaMemcpyHostToDevice); 

    //3. Define Block and Thread Structure
    dim3 dimGrid(GridSize);
    dim3 dimBlock(BlockSize);

    //4. Execute
    for (t=0;t<Ntime;t++) {
        DHB2<<<dimGrid,dimBlock>>>(Tgpu,dTgpu);
        ODE<<<dimGrid,dimBlock>>>(Tgpu,dTgpu);
     }

    //5. Copy Output from GPU to CPU
    cudaMemcpy(Tcpu,Tgpu,M*sizeof(int),cudaMemcpyDeviceToHost);
    for (i = 0;i < M;i++ ) printf("%f \n",*(Tcpu+i));

    //6. Free Mem on CPU and GPU
    free(Tcpu);free(dTcpu);
    cudaFree(Tgpu);cudaFree(dTgpu);
    return 0;
}
