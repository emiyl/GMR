#pragma once

#include <cstddef>

namespace MemoryManager
{
    void* _Alloc(std::size_t size, const char*, int, bool);
    void Free(void* ptr, bool);
    void DumpMemory(void*, void*, bool);
}