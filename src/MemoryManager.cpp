#include "MemoryManager.h"

namespace MemoryManager
{
    void* _Alloc(size_t size, const char*, int, bool)
    {
        return ::operator new(size);
    }

    void Free(void* ptr, bool)
    {
        if (ptr != nullptr)
            ::operator delete(ptr);
    }

    void DumpMemory(void*, void*, bool)
    {
    }
}