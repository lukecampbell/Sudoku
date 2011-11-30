// DiagBoard.cpp
// Luke Campbell
// 29 Nov 11
// The implementation of the DiagBoard class
#include "DiagBoard.hpp"

DiagBoard::DiagBoard()
   :Board(29)
{
   int allocs=0;
   try {
   Square *lineup[9];
   //------------------------------------------------
   // Allocate the clusters for the diagonals
   //------------------------------------------------
   // upper left to lower right (increment)
   for(int k=0;k<9;k++)
   {
      lineup[k] = board[9 * k + k];

   }
   board_clusters[27] = new Cluster(CLUSTER_DIAGONAL, lineup);
   allocs++;


   //------------------------------------------------
   // Allocate the clusters for the diagonals
   //------------------------------------------------
   // upper right to lower left
   for(int k=0;k<9;k++)
   {
      lineup[k] = board[9*k + (8-k)];
   }
   board_clusters[28] = new Cluster(CLUSTER_DIAGONAL, lineup);
   } catch(bad_alloc &ba) {
      delete board_clusters[27];
      throw FatalException(
     "DiagBoard::DiagBoard(): Failed to allocate enough memory for clusters.");
   }
}

Cluster* DiagBoard::getCluster(ClusterType type, int clusterNum)
{
   if(type == CLUSTER_DIAGONAL)
   {
      if(clusterNum < 0 || clusterNum > 1)
         throw FatalException(
               "DiagBoard::getCluster(): index is out of bounds.");
   }
   return Board::getCluster(type,clusterNum);
}


DiagBoard::~DiagBoard()
{
   
}
