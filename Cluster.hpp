// Cluster.hpp
// Lucas Campbell
// 22 Sep 2011
// Cluster.hpp contains the declaration for the Cluster class

#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_

// INCLUDES AND MACROS
#include "Square.hpp"
#include "IllegalInput.hpp"
#include "FatalException.hpp"
#include "MemoryManagement.hpp"


// END INCLUDES AND MACROS


// Enumeration for the three classes of Clusters
// CLUSTER_ROW - is an array of nine Squares logically arranged in a Row
// CLUSTER_COL - is an array of nine Squares logically arranged in a Column
// CLUSTER_BOX - is an array of nine Squares logically arranged in a Box (3x3)
enum ClusterType { CLUSTER_ROW, CLUSTER_COL, CLUSTER_BOX, CLUSTER_DIAGONAL};

class Square;

class Cluster : public MemoryManagement
{
private:
    static const char *cluster_type_string[4];    // for the string enumeration
    static int referenceCount;
    ClusterType cluster_type;          // The type of the cluster
    Square *cluster_group[9];        // Squares in the cluster
    int references[9];              // keep track of what numbers are used


public:
    Cluster();                                      // default constructor (n/a)
    Cluster(ClusterType type, Square *squares[9]);  //
    ~Cluster();                                     // destructor

    ostream& print(ostream &out);                   // prints Cluster info

    // Returns the reference count of this class
    static int refCount() { return referenceCount; }
    // shoops a given square
    void shoop(Square *s, char val);                
    // unshoops a given square
    void unshoop(Square *s, char val);
    // Returns a square in the group
    Square* getSquare(int index);
    // returns true if the value is referenced by this cluster
    bool isReferenced(int n);
};
inline ostream& operator<<(ostream& out,Cluster &c)
{
    return c.print(out);
}

#endif // CLUSTER_HPP__
