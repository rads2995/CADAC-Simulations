# HOPE: Highly Operational Programming Enviroment

Numerical simulation for state-space systems.

Number of states must be declare at compile-time. However, various simulation parameters can be modified at runtime.

### What's Good
- System's matrices and vectors can be resized at runtime

### What is Not
- Number of states must be known at compile-time (modify on include/constants.h)
- Read system's matrices and vectors from text file
- User can modify components of state matrices and vectors at runtime
- No documentation on how to use this

### Requirements
- Build:
  - CMake
<br/><br/>
- Optional:
  - Numpy
  - Matplotlib

### Project Structure
- include/  (header files)
- lib/      (external libraries)
- python/   (python scripts)
- src/      (source code files)

### External Libraries
- Boost: provides free peer-reviewed portable C++ source libraries
  - odeint: a library for solving initial value problems (IVP) of ordinary differential equations
<br/><br/>
- Eigen: a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms
  - Core: includes Matrix and Array classes, basic linear algebra (including triangular and selfadjoint products), array manipulation
