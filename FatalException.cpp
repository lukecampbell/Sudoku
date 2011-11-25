// FatalException.cpp
// The implementation for FatalException
// Luke Campbell
// 24 Nov 2011

#include "FatalException.hpp"

FatalException::FatalException(string message)
   :information(message)
{

}

FatalException::~FatalException()
{

}

const char *FatalException::what()
{
   return information.c_str();
}

ostream& FatalException::print(ostream& out)
{
   out<<what();
   return out;
}


