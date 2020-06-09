#include "JMemory.h"

JMemory::JMemory(size_t size) {
    FreeBlocks = (MemoryBlock*)malloc(size);
    FreeBlocks->Info.NextBlock = nullptr;
    FreeBlocks->Info.Size = size;
    AllMemory = FreeBlocks;
}

JMemory::~JMemory() {
    free(AllMemory);
}

void* JMemory::Allocate(size_t size) {
    MemoryBlock* currentBlock = FreeBlocks;
    while (currentBlock != nullptr) {
        if (size <= currentBlock->Info.Size) {
            MemoryBlock* NextBlock = (MemoryBlock*)((char*)currentBlock + sizeof(MemoryBlock) + size);
            NextBlock->Info.Size = currentBlock->Info.Size - size;
            NextBlock->Info.NextBlock = currentBlock->Info.NextBlock;
            currentBlock->Info.Size = size;

            if (currentBlock == FreeBlocks) {
                FreeBlocks = NextBlock;
            }

            currentBlock->Data = (void*)((char*)currentBlock + sizeof(MemoryBlockData));
            return currentBlock->Data;
        }

        currentBlock = currentBlock->Info.NextBlock;
    }

    return nullptr;
}

void JMemory::Free(void* memory) {
    memory = (char*)(memory) - sizeof(MemoryBlockData);
    MemoryBlock* blockOfMemory = (MemoryBlock*)memory;
    blockOfMemory->Data = nullptr;
    blockOfMemory->Info.NextBlock = FreeBlocks;
    FreeBlocks = blockOfMemory;
}
