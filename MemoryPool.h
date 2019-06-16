#pragma once
#include <cstddef>
class MemoryPool{
public:
    static void* allocate(std::size_t bytes);
    static int deallocate(void* p,std::size_t bytes);
    static void* reallocate(void* p, std::size_t originalSize,std::size_t newSize);

    MemoryPool(){}
    ~MemoryPool(){}
};