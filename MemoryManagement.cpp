// MemoryManagement.cpp
// Luke Campbell
// MemoryManagement Class Definition
// Maintains a refernece count of objects
//

#include "MemoryManagement.hpp"

int MemoryManagement::referenceCount(0);

MemoryManagement::MemoryManagement()
{
   referenceCount++;
}
MemoryManagement::MemoryManagement(MemoryManagement &o)
{
   referenceCount++;
}

MemoryManagement::~MemoryManagement()
{
   referenceCount--;
}

int MemoryManagement::refCount()
{
   return referenceCount;
}

