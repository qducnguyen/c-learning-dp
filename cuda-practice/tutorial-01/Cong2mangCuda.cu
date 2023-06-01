//Tính tổng của 2 mảng dùng chương trình song song CUDA 
#include <stdio.h>
#include <malloc.h>
#include <cuda.h>
#define N 128
#define Nr_Thread_Points 4

// Kernel
__global__ void KernelTinhTong2Mang(int *a, int *b, int *c) 
{	int i,index, start, stop;
	index = blockIdx.x * blockDim.x + threadIdx.x;
    start = index*Nr_Thread_Points;
    stop  = start + Nr_Thread_Points;
    for (i=start;i<stop;i++)
		*(c + i) = *(a + i) + *(b + i);
}

int main(void) { 
// Host code
  	int i,*a_cpu, *b_cpu, *c_cpu; 
  	a_cpu = (int *) malloc (N*sizeof(int));
	b_cpu = (int *) malloc (N*sizeof(int));
	c_cpu = (int *) malloc (N*sizeof(int));
  	for (i = 0; i < N; i++) {
    	*(a_cpu+i) = i * 2;
    	*(b_cpu+i) = i * 3;
  }
//Khai báo biến trên GPU
	int *a_gpu, *b_gpu, *c_gpu;
	cudaMalloc((void**)&a_gpu,N*sizeof(int));
	cudaMalloc((void**)&b_gpu,N*sizeof(int));
	cudaMalloc((void**)&c_gpu,N*sizeof(int));
//Copy Input CPU -> GPU
	cudaMemcpy(a_gpu, a_cpu, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(b_gpu, b_cpu, N*sizeof(int), cudaMemcpyHostToDevice);
//Define structure: Thread, block
    int SoLuongBlocks, SoLuongThreads;
    SoLuongBlocks = 4;
    SoLuongThreads = N/(SoLuongBlocks*Nr_Thread_Points); 
	dim3 dimBlock(SoLuongThreads);
	dim3 dimGrid(SoLuongBlocks);
//Invoke Kernel
	KernelTinhTong2Mang<<<dimGrid,dimBlock>>>(a_gpu,b_gpu,c_gpu);
//Copy Output GPU -> CPU
	cudaMemcpy(c_cpu, c_gpu, N*sizeof(int), cudaMemcpyDeviceToHost);
//Giải phóng bộ nhớ trên GPU
	cudaFree(a_gpu);cudaFree(b_gpu);cudaFree(c_gpu);
// In KQ
  for (i = 0; i < N; i++) printf("%d  ",*(c_cpu+i));
  printf("\n");
return 0;
}
