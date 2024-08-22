#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    int n = 10;

    std::vector<int> vetor_soma(n);
    std::vector<int> vetor_produto(n);

    for (int i = 0; i < n; ++i) {
        vetor_soma[i] = i + 1;
        vetor_produto[i] = i + 1;
    }

    long long soma_total = 0;
    long long produto_total = 1;

    omp_set_num_threads(2);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < n; ++i) {
                soma_total += vetor_soma[i];
            }
            std::cout << "Soma total: " << soma_total << std::endl;
        }
        #pragma omp section
        {
            for (int i = 0; i < n; ++i) {
                produto_total *= vetor_produto[i];
            }
            std::cout << "Produto total: " << produto_total << std::endl;
        }
    }

    return 0;
}
