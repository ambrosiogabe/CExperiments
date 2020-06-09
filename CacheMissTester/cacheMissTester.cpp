#include <chrono>

using namespace std::chrono;

int main() {
    const int xWidth = 4096;
    const int yHeight = 4096;
    float* mem = new float[xWidth * yHeight];
    int iteration = 0;

    for (iteration=0; iteration < 100; iteration++) {
        auto start = high_resolution_clock::now();
        for (int x=0; x < xWidth; x++) {
            for (int y=0; y < yHeight; y++) {
                mem[y * xWidth + x] = 3;
            }
        }
        auto stop = high_resolution_clock::now();
        printf("%d, %I64d, ", iteration, (long long)duration_cast<microseconds>(stop - start).count());

        start = high_resolution_clock::now();
        for (int y=0; y < yHeight; y++) {
            for (int x=0; x < xWidth; x++) {
                mem[y * xWidth + x] = 2;
            }
        }
        stop = high_resolution_clock::now();
        printf("%I64d\n", (long long)duration_cast<microseconds>(stop - start).count());
    }

    return 0;
}