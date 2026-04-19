#include "pi_lib.h"
#include <thread>
#include <vector>
#include <cmath>

double calculate_pi_slice(long long start, long long end, double step) {
    double partial_sum = 0.0;
    for (long long i = start; i < end; ++i) {
        double x = (i + 0.5) * step;
        partial_sum += 4.0 / (1.0 + x * x);
    }
    return partial_sum;
}

double calculate_pi_integration(long long num_steps, unsigned int num_threads) {
    if (num_steps <= 0) return 0.0;
    if (num_threads == 0) num_threads = 1;

    const double step = 1.0 / static_cast<double>(num_steps);
    std::atomic<double> global_sum(0.0);
    std::vector<std::thread> threads;

    long long slice_size = num_steps / num_threads;
    for (unsigned int i = 0; i < num_threads; ++i) {
        long long start = i * slice_size;
        long long end = (i == num_threads - 1) ? num_steps : (i + 1) * slice_size;
        threads.emplace_back([start, end, step, &global_sum]() {
            double partial = calculate_pi_slice(start, end, step);
            double current = global_sum.load();
            while (!global_sum.compare_exchange_weak(current, current + partial));
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    return global_sum.load() * step;
}