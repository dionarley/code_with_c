#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>
#include <thread>
#include <cmath>
#include <vector>
#include "pi_lib.h"

const double PI_REFERENCE = 3.14159265358979323846;

TEST_CASE("calculate_pi_slice - basic computation") {
    double step = 1.0 / 1000.0;
    double result = calculate_pi_slice(0, 1000, step);
    CHECK(result > 3000.0);
    CHECK(result < 3200.0);
}

TEST_CASE("calculate_pi_slice - empty range") {
    double step = 1.0 / 1000.0;
    double result = calculate_pi_slice(0, 0, step);
    CHECK(result == 0.0);
}

TEST_CASE("calculate_pi_slice - single iteration") {
    double step = 1.0 / 1000.0;
    double result = calculate_pi_slice(0, 1, step);
    CHECK(result > 3.0);
    CHECK(result < 5.0);
}

TEST_CASE("calculate_pi_integration - zero steps") {
    double result = calculate_pi_integration(0, 1);
    CHECK(result == 0.0);
}

TEST_CASE("calculate_pi_integration - zero threads fallback") {
    double result = calculate_pi_integration(1000, 0);
    CHECK(result > 3.0);
    CHECK(result < 4.0);
}

TEST_CASE("calculate_pi_integration - single step") {
    double result = calculate_pi_integration(1, 1);
    CHECK(result > 3.0);
    CHECK(result < 4.0);
}

TEST_CASE("calculate_pi_integration - small steps accuracy") {
    double result = calculate_pi_integration(1000, 1);
    CHECK(std::fabs(result - PI_REFERENCE) < 0.01);
}

TEST_CASE("calculate_pi_integration - medium steps accuracy") {
    double result = calculate_pi_integration(100000, 2);
    CHECK(std::fabs(result - PI_REFERENCE) < 0.0001);
}

TEST_CASE("calculate_pi_integration - large steps accuracy") {
    double result = calculate_pi_integration(1000000, std::thread::hardware_concurrency());
    CHECK(std::fabs(result - PI_REFERENCE) < 0.00001);
}

TEST_CASE("calculate_pi_integration - very large steps") {
    double result = calculate_pi_integration(10000000, std::thread::hardware_concurrency());
    CHECK(std::fabs(result - PI_REFERENCE) < 0.000001);
}

TEST_CASE("calculate_pi_integration - single thread deterministic") {
    double r1 = calculate_pi_integration(10000, 1);
    double r2 = calculate_pi_integration(10000, 1);
    CHECK(std::fabs(r1 - r2) < 1e-10);
}

TEST_CASE("calculate_pi_integration - multi-thread deterministic") {
    double r1 = calculate_pi_integration(10000, 2);
    double r2 = calculate_pi_integration(10000, 4);
    CHECK(std::fabs(r1 - r2) < 1e-10);
}

TEST_CASE("calculate_pi_integration - thread scaling") {
    unsigned int hw_threads = std::thread::hardware_concurrency();
    double r1 = calculate_pi_integration(50000, 1);
    double r4 = calculate_pi_integration(50000, hw_threads);
    CHECK(std::fabs(r1 - r4) < 1e-6);
}

TEST_CASE("thread hardware concurrency") {
    unsigned int count = std::thread::hardware_concurrency();
    CHECK(count >= 1);
    CHECK(count <= 128);
}

TEST_CASE("thread creation") {
    std::vector<std::thread> threads;
    std::atomic<int> counter(0);
    
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&counter]() {
            counter++;
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    CHECK(counter == 4);
}

TEST_CASE("integration result bounds") {
    for (int steps = 10; steps <= 1000000; steps *= 10) {
        double result = calculate_pi_integration(steps, 1);
        CHECK(result > 3.0);
        CHECK(result < 4.0);
    }
}

TEST_CASE("integration precision improves with steps") {
    double e1 = std::fabs(calculate_pi_integration(1000, 1) - PI_REFERENCE);
    double e2 = std::fabs(calculate_pi_integration(100000, 1) - PI_REFERENCE);
    double e3 = std::fabs(calculate_pi_integration(1000000, 1) - PI_REFERENCE);
    
    CHECK(e2 < e1);
    CHECK(e3 < e2);
}

int main(int argc, char** argv) {
    return doctest::Context(argc, argv).run();
}