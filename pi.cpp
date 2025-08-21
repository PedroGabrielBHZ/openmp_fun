#include <iostream>
#include <cmath>
#include <omp.h>
#include <chrono>

const long long num_steps = 1000000000; 
double step;

double sequential_pi() {
    double sum = 0.0;
    for (long long i = 0; i < num_steps; ++i) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    return step * sum;
}

double parallel_pi() {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < num_steps; ++i) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    return step * sum;
}

int main() {
    step = 1.0 / static_cast<double>(num_steps);

    auto start_seq = std::chrono::high_resolution_clock::now();
    double pi_seq = sequential_pi();
    auto end_seq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seq = end_seq - start_seq;

    auto start_par = std::chrono::high_resolution_clock::now();
    double pi_par = parallel_pi();
    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_par = end_par - start_par;

    std::cout.precision(15);
    std::cout << "Sequential Pi: " << pi_seq << "\n";
    std::cout << "Sequential Time: " << elapsed_seq.count() << " seconds\n\n";
    std::cout << "Parallel Pi:   " << pi_par << "\n";
    std::cout << "Parallel Time: " << elapsed_par.count() << " seconds\n";

    return 0;
}