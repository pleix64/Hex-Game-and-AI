//
//  HexBoard.hpp
//  Hex_game
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

enum class COLOR{WHITE=0, BLUE, RED};

ostream& operator<<(ostream& out, const COLOR& color);

inline void take_turns(COLOR& turn) {
    if(turn==COLOR::BLUE)
        turn = COLOR::RED;
    else if(turn==COLOR::RED)
        turn = COLOR::BLUE;
    else
        cout << "Error: current_turn is not properly initialized." << endl;
}

class HexBoard {
public:
    HexBoard(int size);
    
    ~HexBoard();
    
    int getV() {
        // get number of vertices (nodes)
        return V;
    }
    
    int getN() {
        // get side length
        return N;
    }
    
    int getX(int i) {
        return i / N;
    }
    
    int getY(int i) {
        return i % N;
    }
    
    int getNode(int x, int y) {
        return x*N + y;
    }
    
    int getPlayerCoord(int i, COLOR player) {
        return player==COLOR::RED ? getX(i) : getY(i);
    }
    
    template <class InputIt>
    void fill(InputIt first, InputIt last, COLOR curr=COLOR::BLUE) {
        // fill the HexBoard with a sequence of nodes
        // color takes turns with BLUE first by default
        // Can also be used to continue after last partial fill.
        // In that case, should provide starting color.
        if(curr==COLOR::WHITE) {
            cout << "Current color have to be either BLUE or RED.\n";
            return;
        }
        for (InputIt it=first; it!=last; ++it) {
            col[*it] = curr;
            take_turns(curr);
        }
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
    
    int player_move(COLOR player, int node, bool swap_on=false);
    // assign the hexagon (x,y) with COLOR player (BLUE or RED)
    // ensure it is a legal move (not already occupied and in board range)
    // change edge color accordingly if neighbor nodes have the same color
    // return 0 for legal move; 1 for illegal move; 2 for WHITE color.
    
    bool player_won(COLOR player);
    // test whether player won
    // call every time after this player moved
    
    bool player_win(COLOR player);
    // test whether player will win at the endgame of a Monte Carlo sample
    // call from the simulation HexBoard when the board is filled (a winner is guaranteed)
    
    void print();
    
    void draw();
    
private:
    int N; // board size
    int V; // number of nodes
    vector<COLOR> col; // node values of COLOR
    set<int> *adj; // adjancency list, no weight or color value needed. 
    //map<int,COLOR> * adj; // adjancency list, edge value is COLOR
    //map<COLOR,set<pair<int,int> > > open; // each player's open set
    // each element in open set is a pair of node index (second)
    // and its distance to North or West Side (first)
    // once a hexagon is occupied, first add it to player's open set
    //map<COLOR,set<int>> closed; // each player's closed set
    // 1. add player owned nodes on North Side (BLUE) or West Side (RED),
    // 2. move open set elements which are closed set elements' neighbors
    //    to closed set
};

#endif /* HexBoard_hpp */
