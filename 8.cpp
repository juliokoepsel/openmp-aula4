#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    int n = 10;

    std::vector<std::vector<int>> A(n, std::vector<int>(n, 1));
    std::vector<std::vector<int>> B(n, std::vector<int>(n, 2));
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    omp_set_num_threads(4);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            #pragma omp parallel for
            for (int i = 0; i < n / 4; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (int k = 0; k < n; ++k) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        #pragma omp section
        {
            #pragma omp parallel for
            for (int i = n / 4; i < n / 2; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (int k = 0; k < n; ++k) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        #pragma omp section
        {
            #pragma omp parallel for
            for (int i = n / 2; i < 3 * n / 4; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (int k = 0; k < n; ++k) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        #pragma omp section
        {
            #pragma omp parallel for
            for (int i = 3 * n / 4; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (int k = 0; k < n; ++k) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << B[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
