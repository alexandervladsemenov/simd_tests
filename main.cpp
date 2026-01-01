#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <chrono>
int main(int argc, char** argv)
{
	double threshold = 0.999;
	// read threshold from command line if provided
	if (argc > 1)
	{
		threshold = std::stod(argv[1]);
		std::cout << "Using threshold: " << threshold << std::endl;
	}
	else
	{
		std::cout << "Using default threshold: 0.999" << std::endl;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1.0, 1.0);
	constexpr size_t sample_size = 1'000'000'000;
	std::vector<double> samples;
	samples.resize(sample_size);
	// we need to time this loop
	auto start = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < sample_size; ++i)
	{
		samples[i] = dis(gen);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time taken to generate samples: " << duration.count() << " ms" << std::endl;
	double sum = 0.0;

	// time this loop as well
	start = std::chrono::high_resolution_clock::now();
	for (const auto& sample : samples)
	{
		if (sample > threshold)
		{
			sum += std::exp(sample) * std::sin(sample);
		}
		else
		{
			sum += std::exp(-sample) * std::cos(sample);
		}	
	}
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time taken to process samples: " << duration.count() << " ms" << std::endl;


	std::cout << "Final sum: " << sum << std::endl;
	return 0;
}
