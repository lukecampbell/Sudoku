// DiagBoard.hpp
// Luke Campbell
// 29 Nov 11
// The declaration of the DiagBoard class
// a derivation o the board class to support diagonal variation


#ifndef DIAGBOARD_HPP__
#define DIAGBOARD_HPP__

#include "Board.hpp"

class DiagBoard : public Board
{
 public:
    DiagBoard();
    virtual ~DiagBoard();
    virtual Cluster* getCluster(ClusterType type, int cluster);

};


#endif // DIAGBOARD_HPP__
