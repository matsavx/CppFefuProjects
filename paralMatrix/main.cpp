#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <immintrin.h>
#include <cstdint>
#include "fib.cpp"
#include "matrix.cpp"

double Integrate(double a, double b, unsigned n)
{
    double dx = (b-a)/n;
    double Result = 0;
    __m128d X = _mm_set_pd(a+dx, a);
    __m128d DX = _mm_set_pd1(2*dx);
    __m128d Sum = _mm_set_pd1(0);

    unsigned Stride = sizeof(__m128d)/sizeof(double);
    assert(n >= Stride);
    assert(n % Stride == 0);
    for(unsigned int i = 0; i < n; i += Stride)
    {
        Sum = _mm_add_pd(Sum, _mm_mul_pd(X,X));
        X = _mm_add_pd(X, DX);
    }
    Result = _mm_cvtsd_f64(_mm_hadd_pd(Sum, Sum));

    Result *= dx;
    return Result;
}

int main() {
//    auto fib = [](auto fibonacci) {
//        for (unsigned n = 0; n <= 30; ++n) {
//            auto tm0 = std::chrono::steady_clock::now();
//            unsigned res = fibonacci(n);
//            auto dur = std::chrono::steady_clock::now() - tm0;
//            std::cout << "n: " << n << ". Result: " << res << ". Time " <<
//                      std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << "\n";
//        }
//    };
    //fib(Fibonacci_omp);
//    fib(Fibonacci_queue);

    double IntRes = Integrate(-1, 1, 1000000);
    printf("%f\n", IntRes);

    u32 C = 8;
    u32 R = 16;
    double* A = (double* )malloc(C * R * sizeof(double));
    for(u32 I = 0; I < C * R; I++)
    {
        A[I] = I + 20;
    }
    // Print(A, C, R);

    double* B = (double* )malloc(C * R * sizeof(double));
    for(u32 I = 0; I < C * R; I++)
    {
        B[I] = I + 30;
    }
    double* Res = (double* )malloc(C * R * sizeof(double));

    AddMatrixSSE(A, B, C, R, Res);
    Print(Res, C, R);
    return 0;
}