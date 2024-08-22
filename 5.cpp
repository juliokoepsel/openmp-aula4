#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    int n = 1000000;
    std::vector<int> vetor(n);
    for (int i = 0; i < n; ++i) {
        vetor[i] = i + 1;
    }

    long long soma_total = 0;

    omp_set_num_threads(4);

    #pragma omp parallel for reduction(+:soma_total)
    for (int i = 0; i < n; ++i) {
        soma_total += vetor[i];
    }

    std::cout << "Soma total: " << soma_total << std::endl;
    return 0;
}
