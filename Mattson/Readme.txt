
These directories support the parallel programming lectures at ESC'2013.

   CPP_11  : C++'11 threading model ... tested on g++ 4.8 on Apple
   CUDA    : CUDA examples ... WARNING, I CANNOT TEST THESE
   MPI     : MPI Examples ... not tested for latests MPIch release
   OpenCL  : fully tested OpenCL 1.2 on the Apple platform
   OpenMP  : fully tested g++ 4.8 on Apple and Intel's Windows platform

In addition, there is a file defining the licence and a readme file.

     License.txt
     Readme.txt

We have also provided a set of extra exercises should the lecture content 
prove to be too basic (which will surely be the case if you are coming into
the class with parallel programming experience) 

   Challenge_problems

We use the same structure for each programming language directory.   There
is a directory of makefile definition files and a solutions directory

    Make_Def_files
    Solutions

Copy the makefile definition file appropriate to your platform into the root 
directory for our programming language of choice into a file called ...

    make.def

Then to generate and test all the programs for the exericses, type:

    make test

To remove executables and object files, type

   make clean

These same make targets can be used in the solutions directory.

For example, to build the exercises for the OpenMP portion of 
course on an Apple laptop, do the following

   % cp Make_def_files/apple.def make.def
   % make test
   g++ -fopenmp -DAPPLE -c hello.c
   g++ -fopenmp -DAPPLE -o hello hello.o -lm
   g++ -fopenmp -DAPPLE -c pi.c
   g++ -fopenmp -DAPPLE -o pi pi.o -lm
   g++ -fopenmp -DAPPLE -c matmul.c
   g++ -fopenmp -DAPPLE -o matmul matmul.o -lm
   ./hello
      Hello World 
   ./pi

    pi with 100000000 steps is 3.141593 in 1.065240 seconds
    ./matmul
    Order 1000 multiplication in 9.864380 seconds 
    Order 1000 multiplication at 202.749689 mflops

    Hey, it worked
    all done 
    % make clean
    rm -f hello pi matmul  *.o

If you find any problems with these exercises or have any questions,
please contact Tim Mattson at timothy.g.mattson@intel.com

