#include <cuda_runtime.h>

__host__ void vector_add_host(const int* V1, const int* V2, int* result, size_t size) {
    int* V1d, *V2d, *resultd;
    unsigned thread_count = 1024;
    unsigned block_count = (size + thread_count - 1)/thread_count;
    cudaError_t err = cudaMalloc((void**)& V1d, size*sizeof(int));
    if (err != cudaSuccess) exit(-1);
    err = cudaMalloc((void**)&V2d, size*sizeof(int));
    err = cudaMalloc((int*)&resultd, size*sizeof(int));
    err = cudaMemcpy(V1d, V1, sizeof(int)*size, cudaMemcpy HostToDevice);
    err = cudaMemcpy(V2d, V2, sizeof(int)*size, cudaMemcpy HostToDevice);
    vector_add<<<block_count, thread_count>>>(V1d,V2d,resultd,sie);
    err = cudaMemcpy(result, resultd, size*sizeof(int), cudaMemcpy DeviceToHost);
    cudaFree(V1d);
}

__device__ void add_up_block(float* V, size_t count, float* V_reduced) {
    unsigned t = blockIdx.x * blockDim.x + threadIdx.x;
    for(size_t n=1,s=2; n < count; s+=s, n=s){
        if(t+n < count && t%s ==0)
            V[t]+=V[t+n];
        __syncthreads();
    }
}

__device__ void__pack(float* V, size_t count, float* V2) {
    unsigned t = threadIdx.x + blockIdx.x + blockDim.x;
    unsigned t0 = thhreadIdx.x;
    extern __shared__ float VS[];
    V2[t0] = V[t<<10];
}

__global__ void add_vector(float* V, size_t n, float* V_reduce){
    add_up_block(V+blockIdx.x * blockDim.x, blockIdx.x<gridDim.x ? blockDim.x:(n%blockDim.x==0?blockDim.x:n%blockDim.x))
    pack(V,n,V_reduce);
}

__host__ void average(count float* V, size_t n) {
    unsigned T = 1024, B = (n + 1023)/1024;
    float* Vd, *Vr;
    float result;
    float* Vs[2];
    cudaMalloc(&Vd, n*4);
    cudaMalloc(&Vr, n>>8);
    Vs[0]=Vd;
    Vs[1]=Vr;
    unsigned i = 0;
    cudaMemcpy(Vd, n*n, cudaMemcpyHostToDevice);
    while(n>0) {
        add_vector<<<B,T>>>(Vs[i%2], n, Vs[(i+1)%2]);
        n-=min(T,n);
        i++;
    }
    cudaMemcpy(&result, Vs[i%2],4,cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize();
    cudaFree(Vd);
    cudaFree(Vr);
    return result/n;
}