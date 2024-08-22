#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    int n = 1000000;
    int valor_procurado = 12345;

    std::vector<int> vetor(n);
    for (int i = 0; i < n; ++i) {
        vetor[i] = i;
    }

    int posicao_encontrada = -1;

    omp_set_num_threads(4);

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        if (vetor[i] == valor_procurado) {
            #pragma omp critical
            {
                if (posicao_encontrada == -1 || i < posicao_encontrada) {
                    posicao_encontrada = i;
                }
            }
        }
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            if (posicao_encontrada != -1) {
                std::cout << "Valor " << valor_procurado << " encontrado na posição: " << posicao_encontrada << std::endl;
            } else {
                std::cout << "Valor " << valor_procurado << " não encontrado." << std::endl;
            }
        }
    }

    return 0;
}
