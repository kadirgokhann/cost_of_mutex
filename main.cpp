#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

const int LIMIT = 500'000'000;

void increment_without_mutex()
{
    int counter = 0;
    auto start 	= std::chrono::high_resolution_clock::now();

    for (int i = 0; i < LIMIT; ++i)
        ++counter;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Without mutex - Final counter: " << counter
              << ", Time taken: " << duration.count() << " seconds\n";
}

void increment_atomically()
{
    std::atomic<int> counter{0};
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < LIMIT; ++i) {
        ++counter;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "With atomic    - Final counter: " << counter
              << ", Time taken: " << duration.count() << " seconds\n";
}

void increment_with_mutex() {
    int counter = 0;
    std::mutex mtx;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < LIMIT; ++i)
	{
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "With mutex    - Final counter: " << counter
              << ", Time taken: " << duration.count() << " seconds\n";
}

int main()
{
    increment_without_mutex();
	increment_atomically();
    increment_with_mutex();
    return 0;
}
