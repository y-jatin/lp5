#include <iostream>
#include <cuda_runtime.h>
using namespace std;
__global__ void vecMul(int*a,int*b,int* c,int n){
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;
    int sum=0;
    for(int k=0;k<n;++k){
	sum+=(a[row*n+k]*b[k*n+col]);
    }
    c[row*n+col]=sum;
}
int main(){
    int N=2;
    int A[4]={1,2,3,4};
    int B[4]={2,3,4,5};
    int C[4];
    int *X,*Y,*Z;
    int totalsize=4*sizeof(int);
    cudaMalloc(&X,totalsize);
    cudaMalloc(&Y,totalsize);
    cudaMalloc(&Z,totalsize);

    cudaMemcpy(X,A,totalsize,cudaMemcpyHostToDevice);
    cudaMemcpy(Y,B,totalsize,cudaMemcpyHostToDevice);

    dim3 threadsPerBlock2D(2,2);
    dim3 blocksPerGrid2D(1,1);
    vecMul<<<blocksPerGrid2D,threadsPerBlock2D>>>(X,Y,Z,N);
    cudaMemcpy(C,Z,totalsize,cudaMemcpyDeviceToHost);
   
    cout << "Matrix A:\n";
    cout << A[0] << " " << A[1] << "\n" << A[2] << " " << A[3] << "\n";

    cout << "Matrix B:\n";
    cout << B[0] << " " << B[1] << "\n" << B[2] << " " << B[3] << "\n";

    cout << "Matrix C = A x B:\n";
    cout << C[0] << " " << C[1] << "\n" << C[2] << " " << C[3] << "\n";
}
