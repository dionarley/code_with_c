#ifndef PI_LIB_H
#define PI_LIB_H

#include <atomic>
#include <cstddef>
#include <cstdint>

double calculate_pi_integration(long long num_steps, unsigned int num_threads);

double calculate_pi_slice(long long start, long long end, double step);

#endif