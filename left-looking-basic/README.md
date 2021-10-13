# Left-looking Algorithm

## Core concepts

### Introduction

All matrices can be represented by a matrix of matrices of dimensions $3 \times 3$.

$A =
\begin{bmatrix}
a_{1,1} & a_{1,2} & a_{1,3} \\
a_{2,1} & a_{2,2} & 1_{2,3} \\
a_{3,1} & a_{3,2} & 1_{3,3} \\
\end{bmatrix$

The algorithm relies on the middle element ($a_{2,2}$) being positioned at the pivot/middle element along the diagonal. Thus, the pivot will assume the position $a_{1,1}$, then $a_{2,2}$, then $a_{3,3}$, and so on. The rest of the $3\times 3$ matrix, as discussed above, will follow this middle element, taking on the forms of nonexistent (ie $a_{1,1}$ when $a_{2,2} = m_{1,1}$), scalar (same idea when $a_{2,2} = m_{2,2}$), vectors, or even submatrices of the original $m$ matrix.

Note that while the convention is to represent vectors and scalars as lowercase
and matrices/submatrices as uppercase, I will not be consistent in this readme.

### Left-looking equations

The three main steps are given by the following:

1. $L_{1,1} u_{1,2} = a_{1,2}$

  - The value of $u_{1,2}$ is the only unknown. ($L_{1,1} = 1$ for the first iteration)
  - We do not solve using inverse of the L matrix (which would be wildly inefficient)
    - Instead, we take advantage of the fact that the L matrix is always lower-triangular (because it's been solved) and apply basic gaussian elimination/triangular solution to calculate the values of the u vector. 

2. $l_{2,1} u_{1,2} + u_{2,2} = a_{2,2}$

  - The value of $u_{2,2}$ is the only unknown and is being solved for.

3. $L_{3,1} u_{1,2} + l_{3,2} u_{2,2} = a_{3,2}$

  - Only $l_{3,2}$ is unknown, so this is easily solved for. 
  - As division is an expensive operation, you are much better off caching the value of $1/u_{2,2}$ instead of dividing every element by it. The compiler might already do this but I don't know. 