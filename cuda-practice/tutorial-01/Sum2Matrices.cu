#include <stdio.h>
#include <malloc.h>
#include <cuda.h>

#define M 16	// row
#define N 32	// col
#define GridSizeX 2 
#define GridSizeY 2
#define BlockSizeX 2
#define BlockSizeY 4
#define ThreadSizeX M / (GridSizeX * BlockSizeX) 
#define ThreadSizeY N / (GridSizeY * BlockSizeY) 

// Kernel
__global__ void SumOfTwoMatricesKernel(int *A, int *B, int *C) 
{	
	int indexX, indexY;
	indexX = threadIdx.x + blockIdx.x*blockDim.x ;
	indexY = threadIdx.y + blockIdx.y*blockDim.y;

	int startX = indexX * ThreadSizeX;
  int stopX  = startX + ThreadSizeX;
  int startY = indexY * ThreadSizeY;
  int stopY  = startY + ThreadSizeY;

  for (int i = startX; i < stopX; i++){
  	for (int j = startY; j < stopY;j++){
  		*(C + i*N+j) = *(A + i*N+j)  + *(B + i*N+j); 
  	}
  }
}

int main(void) { 
// Host code
  int i, j, *A_cpu, *B_cpu, *C_cpu; 
  // Declaration on CPU 
  A_cpu = (int *) malloc (N*M*sizeof(int));
	B_cpu = (int *) malloc (N*M*sizeof(int));
	C_cpu = (int *) malloc (N*M*sizeof(int));
		// Declaration
  	for (i = 0; i < M; i++) {
  		for (j = 0; j < N;j++){
  			 	*(A_cpu+i*N+j) = (i*N+j) * 2;
    			*(B_cpu+i*N+j) = (i*N+j) * 3;
  		}
  }
	//	Declaration on GPU
	int *A_gpu, *B_gpu, *C_gpu;
	cudaMalloc((void**)&A_gpu,N*M*sizeof(int));
	cudaMalloc((void**)&B_gpu,N*M*sizeof(int));
	cudaMalloc((void**)&C_gpu,N*M*sizeof(int));
	
	//Copy Input CPU -> GPU
	cudaMemcpy(A_gpu, A_cpu, N*M*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(B_gpu, B_cpu, N*M*sizeof(int), cudaMemcpyHostToDevice);
	
	//Define structure: Thread, block
	dim3 dimGrid(GridSizeX, GridSizeY);
	dim3 dimBlock(BlockSizeX, BlockSizeY);

	//Invoke Kernel
	SumOfTwoMatricesKernel<<<dimGrid,dimBlock>>>(A_gpu,B_gpu,C_gpu);

	//Copy Output GPU -> CPU
	cudaMemcpy(C_cpu, C_gpu, N*M*sizeof(int), cudaMemcpyDeviceToHost);
		for (i = 0; i < M; i++) {
  		for (j = 0; j < N;j++){
  			  printf("%d ", *(C_cpu+i*N+j));
  		}
  		printf("\n");
  	}

	//Free Memomry
	cudaFree(A_gpu);cudaFree(B_gpu);cudaFree(C_gpu);
	free(A_cpu); free(B_cpu);free(C_cpu);
}
