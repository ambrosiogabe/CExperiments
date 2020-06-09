#ifndef JADE_MEMORY
#define JADE_MEMORY

#include <stdlib.h>

struct MemoryBlock;
struct MemoryBlockData {
    size_t Size;
    MemoryBlock* NextBlock;
};

struct MemoryBlock {
    MemoryBlockData Info;
    void* Data;
};

class JMemory {
public:
    JMemory(size_t size);
    ~JMemory();

    void* Allocate(size_t size);
    void Free(void* Memory);

private:
    MemoryBlock* FreeBlocks;
    MemoryBlock* AllMemory;
};

#endif