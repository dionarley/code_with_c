#include <iostream>
#include <thread>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include "pi_lib.h"

int main(int argc, char* argv[]) {
    long long num_steps = 1000000000;
    
    if (argc > 1) {
        num_steps = std::stoll(argv[1]);
    }
    
    const unsigned int num_threads = std::thread::hardware_concurrency();

    std::cout << "--- Stress Test Iniciado ---" << std::endl;
    std::cout << "Threads: " << num_threads << std::endl;
    std::cout << "Passos: " << num_steps << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    double pi = calculate_pi_integration(num_steps, num_threads);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "--- Resultado ---" << std::endl;
    std::cout << "Valor de PI: " << std::setprecision(15) << pi << std::endl;
    std::cout << "Tempo decorrido: " << elapsed.count() << " segundos" << std::endl;

    return 0;
}