#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <cmath>

std::atomic<double> global_sum(0.0);
std::atomic<unsigned long long> iterations_done(0);

void calculate_slice(long long start, long long end, double step) {
    double partial = 0.0;
    for (long long i = start; i < end; ++i) {
        double x = (i + 0.5) * step;
        partial += 4.0 / (1.0 + x * x);
        iterations_done++;
    }
    
    double current = global_sum.load();
    while (!global_sum.compare_exchange_weak(current, current + partial));
}

int main(int argc, char* argv[]) {
    long long num_steps = 1000000;
    std::string output_file = "pi_progress.log";
    int log_interval_ms = 500;
    
    if (argc > 1) num_steps = std::stoll(argv[1]);
    if (argc > 2) output_file = argv[2];
    if (argc > 3) log_interval_ms = std::stoi(argv[3]);
    
    std::ofstream log(output_file);
    if (!log.is_open()) {
        std::cerr << "Erro: Nao foi possivel criar " << output_file << std::endl;
        return 1;
    }
    
    unsigned int num_threads = std::thread::hardware_concurrency();
    double step = 1.0 / (double)num_steps;
    
    log << "=== Calculo de Pi (Integracao) ===" << std::endl;
    log << "Passos: " << num_steps << std::endl;
    log << "Threads: " << num_threads << std::endl;
    log << "Intervalo log: " << log_interval_ms << "ms" << std::endl;
    log << std::endl;
    log.flush();
    
    std::cout << "======================================" << std::endl;
    std::cout << "  Calculo de Pi - Progresso" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Passos: " << num_steps << std::endl;
    std::cout << "Threads: " << num_threads << std::endl;
    std::cout << "Output: " << output_file << std::endl;
    std::cout << "Para ver progresso:" << std::endl;
    std::cout << "  tail -f " << output_file << std::endl;
    std::cout << std::endl;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;
    long long slice_size = num_steps / num_threads;
    
    for (unsigned int i = 0; i < num_threads; ++i) {
        long long start = i * slice_size;
        long long end = (i == num_threads - 1) ? num_steps : (i + 1) * slice_size;
        threads.emplace_back(calculate_slice, start, end, step);
    }
    
    auto last_log = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds interval(log_interval_ms);
    
    while (iterations_done.load() < (unsigned long long)num_steps) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto now = std::chrono::high_resolution_clock::now();
        
        if (now - last_log >= interval) {
            double elapsed = (now - start_time).count() / 1e9;
            unsigned long long done = iterations_done.load();
            double progress = 100.0 * done / num_steps;
            double speed = elapsed > 0 ? done / elapsed : 0;
            
            log << "Progresso: " << std::fixed << std::setprecision(1) << progress << "% | ";
            log << "Iter: " << done << " / " << num_steps << " | ";
            log << "Tempo: " << std::fixed << std::setprecision(1) << elapsed << "s";
            if (speed > 0) {
                double eta = (num_steps - done) / speed;
                log << " | ETA: " << std::fixed << std::setprecision(0) << eta << "s";
            }
            log << std::endl;
            log.flush();
            
            std::cout << "\r" << std::fixed << std::setprecision(1) << progress << "% | "
                    << done << " / " << num_steps << "          " << std::flush;
            
            last_log = now;
        }
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    double pi = global_sum * step;
    auto end_time = std::chrono::high_resolution_clock::now();
    double total_time = (end_time - start_time).count() / 1e9;
    
    std::cout << std::endl;
    
    log << std::endl;
    log << "=== RESULTADO ===" << std::endl;
    log << "Pi: " << std::fixed << std::setprecision(15) << pi << std::endl;
    log << "Tempo: " << std::fixed << std::setprecision(2) << total_time << "s" << std::endl;
    log << "Velocidade: " << (num_steps / total_time) << " iter/s" << std::endl;
    
    log.close();
    
    std::cout << std::endl;
    std::cout << "=== RESULTADO ===" << std::endl;
    std::cout << "Pi: " << std::fixed << std::setprecision(15) << pi << std::endl;
    std::cout << "Tempo: " << total_time << "s" << std::endl;
    std::cout << "Arquivo: " << output_file << std::endl;
    
    return 0;
}