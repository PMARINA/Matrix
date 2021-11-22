# Matrix

## What is this?

This is a semester-long project implementing known versions of [LU Decomposition](http://www.netlib.org/utk/papers/outofcore/paper.html)

### Why LU Decomposition

It is one of the more efficient ways to solve linear systems of equations. For example, if you had (x + y = 10; x - y = 4), for a computer to solve it, you would need to perform something along the lines of [Gaussian Elimination](https://en.wikipedia.org/wiki/Gaussian_elimination) to allow you to solve one equation and substitute the results into another, and so-forth, until you had the correct answer.

Applications of LU Decomposition includes anything that involves linear solvers, from simple optimization problems, to simulations relying on variants of Newton's method.

## Structure of the Project

As of 2021-11-22, everything in this repo runs solely on dense matrices. The input matrix parser does not fully implement the mtx format, so please only feed sparse general matrices. 

Gaussian and Doolittle are the primitive version of solvers, not particularly efficient or fast, and I believe they can only run single-threadedly

Left-looking and right-looking refer to the memory accesses. Left-looking only looks to the left, while right-looking only looks to the right. Both methods have the same complexity. I would recommend left-looking if you had to worry about large matrices and rounding errors; however, right-looking is accurate to the underlying limit of the double, in my testing with toy-matrices.

Blocked refers to the memory access pattern. A blocked implementation is both parallelizeable and results in much better performance due to the speed of cache.

While blocked-left-looking isn't implemented (yet), it should be possible to implement, though I'm not sure of the performance.

## Limitations

The parser isn't a proper implementation of an mtx parser. Nothing is formatted in a way that is extensible (ie using OOP). This is intentional to maximize performance (context switching). This also means when the code fails, you will get weird output and no indication of failure. Check your outputs against matlab/etc.

Also, \[matrix_dimension\] % \[block_dimension\] must equal 0. This isn't a limitation of the algorithm; just my implementation of it. It could be solved if you added some sort of tracking of the matrix size and the current indices to compute, in the individual thread, whether to limit the indices to less than block_size. 

## What's happening?

I'm learning to program FPGAs, in an effort to port this over to an FPGA. 

## Future Improvements

- Implement symbolic factorization
  - Sparse matrices
- Cholesky Factorization
