// simulate_system.h: header file containing various functions
#ifndef SIMULATE_SYSTEM_H
#define SIMULATE_SYSTEM_H

// Include necessary Standard Library headers
#include <iostream>
#include <fstream>

// Define data type for dynamic-size matrices 
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> state_type;

// Define template state-space system function 
template<typename T> 
void state_function (const T &x, T &dxdt, double t);

// Define template function to write state solutions
template<typename T> 
void write_states (const T &x, const double t);

// Define template function to write output solutions
void write_output (const state_type &y);

// Function definition to simulate system based on number of states
template<typename T> 
void simulate_system(double t0, double tf, double step_size);

#endif // SIMULATE_SYSTEM_H
