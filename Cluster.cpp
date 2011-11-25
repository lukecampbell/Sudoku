// Cluster.cpp
// Lucas Campbell
// 22 Sep 2011
// Cluster.cpp contains the implementation for the Cluster Class

#include "Cluster.hpp"
#include "Square.hpp"
const char *Cluster::cluster_type_string[] = { "Row", "Column", "Box" };

//-----------------------------------------------------------------------------
// Cluster()
// Default constructor
Cluster::Cluster()
{
    for (int k = 0; k < 9; k++)
        references[k] = 0; //tracks what numbers are used

}

//-----------------------------------------------------------------------------
// Cluster()
// Default desconstructor
Cluster::~Cluster()
{
#ifdef __DEBUG__
    DEBUG_CALL(~Cluster(),__LINE__);
    cerr<<"Cluster: "<<this<<" destroyed"<<endl;
#endif // __DEBUG__
}

//-----------------------------------------------------------------------------
// Square()
// Constructor
// ClusterType type - the type to be used to define the cluster
// Square *squares[9] - An array of nine squares to define the cluster
Cluster::Cluster(ClusterType type, Square *squares[9])
{
    int k = 0;
    for (k = 0; k < 9; k++)
        references[k] = 0; //tracks what numbers are used
    //------------------------------------------------
    // Check to see if **squares is null
    //------------------------------------------------
    if (!squares)
    {
        throw FatalException("Cluster::Cluster() null pointer in parameter");
    }

    cluster_type = type;
    //------------------------------------------------
    // Initialize the squares using the provided array
    // TODO: we need to find a way to check for segment bounds
    //------------------------------------------------
    for (k = 0; k < 9; k++)
    {
        if (!squares[k])
        {
           throw FatalException("Cluster::Cluster() null pointer in parameter");
        }
        cluster_group[k] = squares[k];

    }
    for (k = 0; k < 9; k++)
        cluster_group[k]->addCluster(this);
}
//-----------------------------------------------------------------------------
// Shoop()
//
// Square *s - the square in the cluster to modify
// char val - the Value to put in place and eliminate in adjacent squares
// No return value
void Cluster::shoop(Square *s, char val)
{
    int k = 0;
    if(val=='0' || val=='-')
       return;
    if (val < '0' || val > '9')
    {
        throw IllegalInput(s->getRow(),s->getCol(),val,
              "Invalid character input");
    }

    int ref = val - '1';
    references[ref]++;

    // Turn off 'val' for each square except the one pointed to by s

    for (k = 0; k < 9; k++)
    {
        if (s == cluster_group[k])
            continue;
        cluster_group[k]->turnOff(val - '0');

    }

}
void Cluster::unshoop(Square *s, char val)
{
    if(val=='0' || val=='-' || val==' ')
       return;
    if (val < '0' || val > '9')
    {
        char errmsg[] = "Invalid character input\n";
        fatal(errmsg);
    }
    int ref = val -'1';
    if(references[ref]>0)
        references[ref]--;
    if(references[ref]==0) // there are no more references
    {
        for(int k=0;k<9;k++)
        {
            if(s==cluster_group[k])
                continue;
            cluster_group[k]->turnOn(val-'0');
        }
    }
}
//-----------------------------------------------------------------------------
// print()
// Prints the logical output of the cluster
// ostream& out - the output stream to be used
// Returns an output stream with the data
ostream& Cluster::print(ostream &out)
{
    int k = 0;
    out << "Cluster is of type: " << cluster_type_string[cluster_type] << endl;
    for (k = 0; k < 9; k++)
        out << *cluster_group[k] << endl;
    out << endl;
    return out;
}
