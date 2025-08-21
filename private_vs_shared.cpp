#include <iostream>
#include <omp.h>

int main() {
    int shared_var = 0;

    std::cout << "Before parallel region: shared_var = " << shared_var << std::endl;

    #pragma omp parallel shared(shared_var)
    {
        int private_var = 0;

        // Each thread increments its private_var and the shared_var
        private_var += omp_get_thread_num();
        #pragma omp critical
        {
            shared_var += omp_get_thread_num();
        }

        std::cout << "Thread " << omp_get_thread_num()
                  << ": private_var = " << private_var
                  << ", shared_var = " << shared_var << std::endl;
    }

    std::cout << "After parallel region: shared_var = " << shared_var << std::endl;

    return 0;
}