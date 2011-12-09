// FatalException.hpp
// The class definition for FatalException
// Luke Campbell
// 24 Nov 2011

#ifndef FATALEXCEPTION_HPP__
#define FATALEXCEPTION_HPP__

#include <string>
#include <iostream>

#include "tools.hpp"

using namespace std;

class FatalException 
{
protected:
   string information;
public:
   FatalException(string message="Error");


   virtual ~FatalException();
   virtual const char *what();
   virtual ostream& print(ostream&);


};

inline ostream& operator<<(ostream& out, FatalException &f)
{
   return f.print(out);
}


#endif // FATALEXCEPTION_HPP__
