#include <iostream>
#include <omp.h>
#include <vector>
#include <random>

int main() {
    int rows = 100;
    int cols = 100;

    std::vector<std::vector<int>> matriz(rows, std::vector<int>(cols, 0));

    std::mt19937 gerador;
    std::uniform_int_distribution<int> distrib(0, 100);

    omp_set_num_threads(4);

    #pragma omp parallel
    {
        #pragma omp single
        {
            std::random_device rd;
            gerador.seed(rd());
        }
        #pragma omp for collapse(2)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matriz[i][j] = distrib(gerador);
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
