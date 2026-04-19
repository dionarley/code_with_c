#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <iomanip>
#include <chrono>

// Função que calcula uma fatia do Stress Test
void calculate_pi_slice(long long start, long long end, double step, std::atomic<double>& global_sum) {
    double partial_sum = 0.0;
    for (long long i = start; i < end; ++i) {
        double x = (i + 0.5) * step;
        partial_sum += 4.0 / (1.0 + x * x);
    }
    
    // Adição atômica para evitar race conditions
    double current_sum = global_sum.load();
    while (!global_sum.compare_exchange_weak(current_sum, current_sum + partial_sum));
}

int main() {
    // Configurações do teste
    const long long num_steps = 1000000000; // 1 bilhão de passos
    const unsigned int num_threads = std::thread::hardware_concurrency();
    const double step = 1.0 / (double)num_steps;
    
    std::atomic<double> global_sum(0.0);
    std::vector<std::thread> threads;
    
    std::cout << "--- Stress Test Iniciado ---" << std::endl;
    std::cout << "Threads detectadas: " << num_threads << std::endl;
    std::cout << "Calculando " << num_steps << " passos..." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Divide o trabalho entre as threads
    long long slice_size = num_steps / num_threads;
    for (unsigned int i = 0; i < num_threads; ++i) {
        long long start = i * slice_size;
        long long end = (i == num_threads - 1) ? num_steps : (i + 1) * slice_size;
        threads.emplace_back(calculate_pi_slice, start, end, step, std::ref(global_sum));
    }

    for (auto& t : threads) {
        t.join();
    }

    double pi = global_sum * step;
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "--- Resultado ---" << std::endl;
    std::cout << "Valor de PI: " << std::setprecision(15) << pi << std::endl;
    std::cout << "Tempo decorrido: " << elapsed.count() << " segundos" << std::endl;

    return 0;
}
