//
//  HexBoard.hpp
//  hw4_Hex_basic
//
/* *******************************************
Coordinate convention in this program:
  0---------------Y
   \
    \
     \
      \
       X
 N: side length
 V: number of nodes, V = N*N
 i is used as index of a node
   ******************************************* */
//  Created by Yu Chen on 1/28/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#ifndef HexBoard_hpp
#define HexBoard_hpp

#include <set>

using namespace std;

class HexBoard {
public:
    HexBoard(int side);
    ~HexBoard();
    int getX(int i) {
        return i / N;
    }
    int getY(int i) {
        return i % N;
    }
    int getNode(int x, int y) {
        return x*N + y;
    }
    void add_neighbor_safe(int i, int x, int y) {
        // add node (x,y) to i's neighbor safely
        // make sure the new neighbor is not outside the board
        // if it's out of the range, nothing is added.
        if(x>=0 && x<N && y>=0 && y<N)
             adj[i].insert(getNode(x,y));
    }
    
    void print();
    
private:
    int N; // side length
    int V; // number of nodes
    set<int> * adj; // adjancency list, no weight needed
};

#endif /* HexBoard_hpp */
