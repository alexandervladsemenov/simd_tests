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
    if (argc > 2) {
        radius = std::stoi(argv[2]);
    }
    if (argc > 3) {
        sigma = std::stof(argv[3]);
    }

    std::vector<float> array(N * N), results(N * N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1.0);
    int sample_size = N * N;
    for (auto& val : array) {
        val = dis(gen);
    }
    auto start = std::chrono::high_resolution_clock::now();
    size_t total_count = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            const int imax = std::min(i + radius, N - 1);
            const int imin = std::max(i - radius, 0);
            const int jmax = std::min(j + radius, N - 1);
            const int jmin = std::max(j - radius, 0);
            const int index_global = N * i + j;
            const float center_val = array[i * N + j];
            float sum_weights = 0.0f;
            float sum_weighted = 0.0f;

            for (int ii = imin; ii <= imax; ++ii) {
                for (int jj = jmin; jj <= jmax; ++jj) {
                    total_count++;
                    int index_local = N * ii + jj;
                    const float diff = center_val - array[index_local];
                    const float w = std::exp(-diff * diff / sigma / sigma / 2);
                    sum_weights += w;
                    sum_weighted += array[index_local] * w;
                }
            }
            results[index_global] = sum_weighted/ sum_weights;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "CPU Time: " << duration.count() << " ms" << std::endl;
    std::cout << "Average " << std::accumulate(results.begin(), results.end(), 0.0) / sample_size << std::endl;
    std::cout << "Total Count " << total_count << std::endl;
    return 0;
}