// Cluster.hpp
// Lucas Campbell
// 22 Sep 2011
// Cluster.hpp contains the declaration for the Cluster class

#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_

// INCLUDES AND MACROS
#include "Square.hpp"


// END INCLUDES AND MACROS


// Enumeration for the three classes of Clusters
// CLUSTER_ROW - is an array of nine Squares logically arranged in a Row
// CLUSTER_COL - is an array of nine Squares logically arranged in a Column
// CLUSTER_BOX - is an array of nine Squares logically arranged in a Box (3x3)
enum ClusterType { CLUSTER_ROW, CLUSTER_COL, CLUSTER_BOX };

class Square;

class Cluster
{
private:
    static const char *cluster_type_string[3];    // for the string enumeration
    ClusterType cluster_type;          // The type of the cluster
    Square *cluster_group[9];        // Squares in the cluster
    int references[9];              // keep track of what numbers are used


public:
    Cluster();                                      // default constructor (n/a)
    Cluster(ClusterType type, Square *squares[9]);  //
    ~Cluster();                                     // destructor
    ostream& print(ostream &out);                   // prints Cluster info
    void shoop(Square *s, char val);                // shoops a given square
    void unshoop(Square *s, char val);
};
inline ostream& operator<<(ostream& out,Cluster &c)
{
    return c.print(out);
}

#endif // CLUSTER_HPP__
