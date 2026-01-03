#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>
#include <numeric>
#include <cstring>

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
    
    const float sigma_sq_inv = -0.5f / (sigma * sigma);


    for (int i = 0; i < N; ++i) {
        const int imin = std::max(i - radius, 0);
        const int imax = std::min(i + radius, N - 1);
        const int actual_rows = imax - imin + 1;
        
       
        for (int j = 0; j < N; ++j) {
            const int jmin = std::max(j - radius, 0);
            const int jmax = std::min(j + radius, N - 1);
            const int actual_cols = jmax - jmin + 1;
            const int index_global = N * i + j;
            const float center_val = array[i * N + j];
            float sum_weights = 0.0f;
            float sum_weighted = 0.0f;
            
            for (int ii = 0; ii < actual_rows; ++ii) {
                const int actual_row = imin + ii;
                const float* row_ptr = &array[actual_row * N + jmin];
                
                for (int jj = 0; jj < actual_cols; ++jj) {
                    const float neighbor_val = row_ptr[jj];
                    const float diff = center_val - neighbor_val;
                    const float diff_sq = diff * diff;
                    const float weight = std::exp(diff_sq * sigma_sq_inv);
                    
                    sum_weights += weight;
                    sum_weighted += weight * neighbor_val;
                    total_count++;
                }
            }
            
            results[index_global] = sum_weighted / sum_weights;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "CPU Time: " << duration.count() << " ms" << std::endl;
    std::cout << "Average " << std::accumulate(results.begin(), results.end(), 0.0)/ sample_size << std::endl;
    std::cout << "Total Count " << total_count << std::endl;
    return 0;
}