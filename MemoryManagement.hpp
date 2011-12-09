// MemoryManagement.hpp
// Luke Campbell
// MemoryManagement Class Declaration
// Maintains a reference count of objects

#ifndef MEMORYMANAGEMENT_HPP__
#define MEMORYMANAGEMENT_HPP__

#include <iostream>

class MemoryManagement
{
protected: 
   static int referenceCount;

public:
   MemoryManagement();
   MemoryManagement(MemoryManagement &o);
   virtual ~MemoryManagement();
   static int refCount();
};


#endif // MEMORYMANAGEMENT_HPP__
