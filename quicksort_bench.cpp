#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

void quicksort(int* a, int left, int right) {
    while (left < right) {
        int i = left;
        int j = right;
        int pivot = a[left + (right - left) / 2];

        while (i <= j) {
            while (a[i] < pivot) ++i;
            while (a[j] > pivot) --j;
            if (i <= j) {
                std::swap(a[i], a[j]);
                ++i;
                --j;
            }
        }

        if (j - left < right - i) {
            if (left < j) {
                quicksort(a, left, j);
            }
            left = i;
        } else {
            if (i < right) {
                quicksort(a, i, right);
            }
            right = j;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Problem size and repetitions
    const int N = 200000;       // array size
    const int R = 50;           // number of runs

    std::vector<int> base(N);

    std::mt19937_64 rng(123456789);
    std::uniform_int_distribution<int> dist(0, 1'000'000);

    for (int i = 0; i < N; ++i) {
        base[i] = dist(rng);
    }

    using clock = std::chrono::high_resolution_clock;
    std::uint64_t checksum = 0;

    auto start = clock::now();
    for (int r = 0; r < R; ++r) {
        std::vector<int> data = base;  // copy to avoid in-place sorted input
        quicksort(data.data(), 0, N - 1);

        // Prevent aggressive optimization (use the result)
        // checksum += static_cast<std::uint64_t>(data[N / 2]);
    }
    auto end = clock::now();

    auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();

    std::cout << "Size=" << N << " Runs=" << R << "\n";
    std::cout << "Elapsed_ms=" << ms << "\n";
    std::cout << "Checksum=" << checksum << "\n";

    return 0;
}