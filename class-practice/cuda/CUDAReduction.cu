#include <stdio.h>
#include <malloc.h>
#include <cuda.h>
#define M       32
#define GridSize 4
#define BlockSize M/GridSize
//
__global__ void reduce0(int *g_idata, int *g_odata){
  extern __shared__ int sdata[M];
// each thread loads one element from global to shared mem
	int tid, i, s;
  tid =  threadIdx.x;
	i = blockIdx.x * blockDim.x + threadIdx.x;
  sdata[tid] = *(g_idata+i);
  __syncthreads();
// do reduction in shared mem
  for(s=1; s < blockDim.x; s *= 2) {
    if(tid%(2*s) == 0){
    sdata[tid] += sdata[tid + s];
    }
    __syncthreads();
  }
// write result for this block to global mem
  if (tid==0) *(g_odata + blockIdx.x) = sdata[0];
}
//=========================
int main(){
        int i, Sumcpu = 0;
        int *Ricpu, *Rocpu;
        Ricpu  = (int *) malloc (M*sizeof(int));
        Rocpu  = (int *) malloc (GridSize*sizeof(int));
        for (i=0; i<M; i++) {*(Ricpu+i) = i+1; Sumcpu = Sumcpu + *(Ricpu+i);}
        printf("Sum by CPU: %d \n", Sumcpu);
     // CUDA code
    //1. Delare and Allocate Mem on GPU
         int *Rigpu,*Rogpu;
         cudaMalloc((void**)&Rigpu ,M*sizeof(int));
         cudaMalloc((void**)&Rogpu ,GridSize*sizeof(int));
    //2. Copy Input from CPU to GPU
         cudaMemcpy(Rigpu,Ricpu,M*sizeof(int),cudaMemcpyHostToDevice);
    //3. Define Block and Thread Structure
         dim3 dimGrid(GridSize);
         dim3 dimBlock(BlockSize);
         reduce0<<<dimGrid,dimBlock>>>(Rigpu,Rogpu);
    //5. Copy Output from GPU to CPU
         cudaMemcpy(Rocpu,Rogpu,GridSize*sizeof(int),cudaMemcpyDeviceToHost);
         printf("Sum by GPU: \n");
         for (i = 0;i < GridSize;i++ ) printf("%d \n",*(Rocpu+i));
    //6. Free Mem on CPU and GPU
         free(Ricpu);free(Rocpu);
         cudaFree(Rigpu);cudaFree(Rigpu);
return 0;
}
