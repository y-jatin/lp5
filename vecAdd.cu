%%writefile vecAdd.cu
#include <iostream>
#include <cuda_runtime.h>
// !nvcc -arch=sm_75 -ccbin=/usr/bin/gcc-11 vecAdd.cu -o vecAdd -lstdc++ && ./vecAdd
using namespace std;
__global__ void vecAdd(int* a,int* b,int*c,int n){
    int tid=blockIdx.x*blockDim.x+threadIdx.x;
    if(tid<n){
	c[tid]=a[tid]+b[tid];
    }
}
int main(){
    int N=5;
    int A[N]={1,2,3,4,5};
    int B[N]={2,3,4,5,6};
    int C[N];
    int totalsize=N*sizeof(int);
    int *X,*Y,*Z;
    cudaMalloc(&X,totalsize);
    cudaMalloc(&Y,totalsize);
    cudaMalloc(&Z,totalsize);
    
    cudaMemcpy(X,A,totalsize,cudaMemcpyHostToDevice);
    cudaMemcpy(Y,B,totalsize,cudaMemcpyHostToDevice);
    vecAdd<<<1,N>>>(X,Y,Z,N);
    cudaDeviceSynchronize();
    cudaMemcpy(C,Z,totalsize,cudaMemcpyDeviceToHost);
    cout<<"A ";
    for(int i=0;i<N;i++) cout<<A[i]<<" ";
    cout<<endl;
    cout<<"B ";
    for(int i=0;i<N;i++) cout<<B[i]<<" ";
    cout<<endl;
    cout<<"C ";
    for(int i=0;i<N;i++) cout<<C[i]<<" ";
    cout<<endl;
}
