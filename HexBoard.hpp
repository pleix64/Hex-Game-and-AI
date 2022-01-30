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
 N: board size
 V: number of nodes, V = N*N
 i is used as index of a node
   ******************************************* */
//  Created by Yu Chen on 1/28/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#ifndef HexBoard_hpp
#define HexBoard_hpp

#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

enum class COLOR: short {WHITE, RED, BLUE};

ostream& operator<<(ostream& out, const COLOR& color);

class HexBoard {
public:
    HexBoard(int size);
    
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
            adj[i].insert(getNode(x, y));
             //adj[i].insert(make_pair(getNode(x,y),COLOR::WHITE));
    }
    
    bool adjacent(int i, int j);
    // test whether there is an edge from node i to node j
    
    int player_move(COLOR player, int x, int y);
    // assign the hexagon (x,y) with COLOR player (RED or BLUE)
    // ensure it is a legal move (not already occupied and in board range)
    // change edge color accordingly if neighbor nodes have the same color
    // return 0 for legal move; 1 for illegal move; 2 for WHITE color.
    
    bool player_won(COLOR player);
    // test whether player won
    // call every time after this player moved
    
    void print();
    
    void draw();
    
private:
    int N; // board size
    int V; // number of nodes
    vector<COLOR> col; // node values of COLOR
    set<int> *adj; // adjancency list, no weight or color value needed. 
    //map<int,COLOR> * adj; // adjancency list, edge value is COLOR
    map<COLOR,set<pair<int,int> > > open; // each player's open set
    // each element in open set is a pair of node index (second)
    // and its distance to North or West Side (first)
    // once a hexagon is occupied, first add it to player's open set
    map<COLOR,set<int>> closed; // each player's closed set
    // 1. add player owned nodes on North Side (RED) or West Side (BLUE),
    // 2. move open set elements which are closed set elements' neighbors
    //    to closed set
};

#endif /* HexBoard_hpp */
