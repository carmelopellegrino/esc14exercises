//------------------------------------------------------------------------------
//
//  PROGRAM: Matrix Multipliplication driver
//
//  PURPOSE: This is a driver program to test various ways of computing
//           the product:
//
//                C  = A * B
//
//           A and B are set to constant matrices so we
//           can make a quick test of the multiplication.
//
//  USAGE:   The matrices are constant matrices, square and the order is
//           set as a constant, ORDER (see mult.h).
//
//  HISTORY: Written by Tim Mattson, August 2010 
//           Modified by Simon McIntosh-Smith, September 2011
//           Modified by Tom Deakin and Simon McIntosh-Smith, October 2012
//             Updated to C++ Wrapper v1.2.6 by Tom Deakin, August 2013
//
//------------------------------------------------------------------------------

#include "matmul.hpp"
#include "matrix_lib.hpp"

extern double wtime();   //portable timer in CPP_common

int main(void)
{

    int Mdim, Ndim, Pdim;   // A[N][P], B[P][M], C[N][M]
    int szA, szB, szC;      // number of elements in each matrix


    double start_time;      // Starting time
    double run_time;        // timing data

    Ndim = ORDER;
    Pdim = ORDER;
    Mdim = ORDER;

    szA = Ndim * Pdim;
    szB = Pdim * Mdim;
    szC = Ndim * Mdim;

    std::vector<float> h_A(szA); // Host memory for Matrix A
    std::vector<float> h_B(szB); // Host memory for Matrix B
    std::vector<float> h_C(szC); // Host memory for Matrix C

    cl::Buffer d_a, d_b, d_c;   // Matrices in device memory

    initmat(Mdim, Ndim, Pdim, h_A, h_B, h_C);

    printf("\n===== Sequential, matrix mult (dot prod), order %d on host CPU ======\n",ORDER);
    for(int i = 0; i < COUNT; i++)
    {
        zero_mat(Ndim, Mdim, h_C);
    //    util::Timer timer;
        start_time = wtime();

        seq_mat_mul_sdot(Mdim, Ndim, Pdim, h_A, h_B, h_C);

       //run_time = static_cast<double>(timer.getTimeMilliseconds())/1000.0;
       run_time  = wtime() - start_time;
        
        results(Mdim, Ndim, Pdim, h_C, run_time);
    }

    return EXIT_SUCCESS;
}
