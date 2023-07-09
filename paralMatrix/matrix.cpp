#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <immintrin.h>
#include <cstdint>
//#include "fib.cpp"

typedef uint32_t u32;

void AddMatrixSSE(const double* A, const double* B, std::size_t C, std::size_t R, double* Result)
{
    assert(C % 8 == 0);
    assert(R % 8 == 0);

    u32 ElementsInRegister = sizeof(__m128d)/sizeof(double);
    assert(ElementsInRegister == 2);
    u32 Iterations = C*R/ElementsInRegister;

    for(u32 I = 0; I < Iterations; I++)
    {
        __m128d ATerm = _mm_load_pd(A);
        __m128d BTerm = _mm_load_pd(B);
        __m128d Sum = _mm_add_pd(ATerm, BTerm);
        _mm_storeu_pd(Result, Sum);

        A += ElementsInRegister;
        B += ElementsInRegister;
        Result += ElementsInRegister;
    }

}

void Print(const double* A, u32 C, u32 R)
{
    for(u32 Y = 0; Y < R; Y++)
    {
        for(u32 X = 0; X < C; X++)
        {
            printf("%f ", A[Y * C + X]);
        }
        printf("\n");
    }
}

void mul_matrix(const double* A, const double* B, size_t rA, size_t cA, size_t cB, double* result) {
    size_t rB = 0;
    if (rA & 7)
        exit(-1);
    for (auto j = 0; j < rA; j += 8) {
        auto tempRes = _mm512_setzero_pd();
        for (auto k = 0; k < cB; k++) {
            for (auto i = 0; i < cA; i++) {
                auto tempA = _mm512_load_pd(&A[i*rA+j]);
                auto tempB = _mm512_set1_pd(B[k*rB+i]);
                tempRes = _mm512_add_pd(_mm512_mul_pd(tempA, tempB), tempRes);
            }
            _mm512_storeu_pd(&result[k*rB+j], tempRes);
        }
    }
}