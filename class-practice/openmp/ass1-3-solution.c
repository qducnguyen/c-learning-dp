#include <stdio.h>
#include <malloc.h>
#include <omp.h>
int main() {
    int N = 64, i, *A;
    A = (int*) malloc(N*sizeof(int));
    for (i=0;i<N;i++) *(A+i) = i; // Input array A
    int id, nthreads = N;
    while (nthreads>1){           // Sum Reduction (Complexity = log2(N))
        nthreads = nthreads/2; omp_set_num_threads(nthreads);
        #pragma omp parallel private(id)
        {
            id = omp_get_thread_num();
            *(A+id) = *(A+id) + *(A+id+nthreads);
    }
    printf("Sum of A = %d \n",*A);
    return 0;        }

}