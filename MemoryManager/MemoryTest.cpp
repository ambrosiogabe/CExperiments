#include <windows.h>
#include <stdio.h>
#include <chrono>
#include "JMemory.h"

class Vector3f {
public:
    Vector3f(float x, float y, float z) :
        x(x), y(y), z(z) {}

    float x, y, z;    
};

class Vector2f {
public:
    Vector2f(float x, float y) :
        x(x), y(y) {}

    float x, y;
};

static JMemory MemoryManager = JMemory(sizeof(char) * 1024 * 1024);
// Remove this macro to overload new operator
#if 0
void* operator new(size_t size) {
    return MemoryManager.Allocate(size);
}

void operator delete(void* memory) {
    MemoryManager.Free(memory);
}
#endif

void* customNew(size_t size) {
    return MemoryManager.Allocate(size);
}

void customDelete(void* memory) {
    MemoryManager.Free(memory);
}

using namespace std::chrono;
int main() {
    const int numVectors = 10000;
    Vector3f* vectors[numVectors];

    auto start = high_resolution_clock::now();
    for (int i=0; i < numVectors; i++) {
        Vector3f* vector = new Vector3f(i, i, i);
        vectors[i] = vector;
    }
    auto stop = high_resolution_clock::now();
    printf("(Default Impl) Time to intialize %d vectors: %I64d microseconds\n", numVectors, (long long)duration_cast<microseconds>(stop - start).count());

    start = high_resolution_clock::now();
    for (int i=0; i < numVectors; i++) {
        delete vectors[i];
    }
    stop = high_resolution_clock::now();
    printf("(Default Impl) Time to delete %d vectors: %I64d microseconds\n", numVectors, (long long)duration_cast<microseconds>(stop - start).count());




    start = high_resolution_clock::now();
    for (int i=0; i < numVectors; i++) {
        Vector3f* vector = (Vector3f*)customNew(sizeof(Vector3f));
        vector->x = i;
        vector->y = i;
        vector->z = i;
        vectors[i] = vector;
    }
    stop = high_resolution_clock::now();
    printf("(Custom Impl) Time to intialize %d vectors: %I64d microseconds\n", numVectors, (long long)duration_cast<microseconds>(stop - start).count());

    start = high_resolution_clock::now();
    for (int i=0; i < numVectors; i++) {
        customDelete(vectors[i]);
    }
    stop = high_resolution_clock::now();
    printf("(Custom Impl) Time to delete %d vectors: %I64d microseconds\n", numVectors, (long long)duration_cast<microseconds>(stop - start).count());

    system("pause");
    return 0;
}