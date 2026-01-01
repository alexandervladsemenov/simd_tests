#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>

int main(int argc, char **argv) {
    int N = 10'000;
    float sigma = 1;
    int radius = 3;
    if (argc > 1) {
        N = std::stoi(argv[1]);
    }
    if ( argc > 2) {
        radius = std::stoi(argv[2]);
    }
    if ( argc > 3) {
        sigma = std::stof(argv[3]);
    }

    std::vector<float> array(N * N), results(N * N);
    std::vector<float> weights((2*radius+1)*(2*radius+1));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1.0);
    int sample_size = N * N;
    for (int i = 0; i < sample_size; ++i) {
        array[i] = dis(gen);
    }
    auto start = std::chrono::high_resolution_clock::now();
    size_t total_count = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int imax = std::min(i + radius, N - 1);
            int imin = std::max(i - radius, 0);
            int jmax = std::min(j + radius, N - 1);
            int jmin = std::max(j - radius, 0);
            int index_global = N * i + j;
            int idx = 0;
            for (int ii = imin; ii <= imax; ++ii) {
                for (int jj = jmin; jj <= jmax; ++jj) {
                    int index_local = N * ii + jj;
                    weights[idx++] = std::exp(-(array[index_global] - array[index_local]) *
                                               (array[index_global] - array[index_local]) / sigma / sigma / 2);
                }
            }
            results[index_global] = 0;
            float weight = 0;
            idx = 0;
            for (int ii = imin; ii <= imax; ++ii) {
                for (int jj = jmin; jj <= jmax; ++jj) {
                    total_count++;
                    int index_local = N * ii + jj;
                    float w = weights[idx++];
                    weight += w;
                    results[index_global] += array[index_local] * w;
                }
            }
            results[index_global] /= weight;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "CPU Time: " << duration.count() << " ms" << std::endl;
    std::cout << "First Element " << results[0] << std::endl;
    std::cout << "Total Count " << total_count << std::endl;
    return 0;
}
