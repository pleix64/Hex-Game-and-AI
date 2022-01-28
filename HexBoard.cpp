//
//  HexBoard.cpp
//  hw4_Hex_basic
//
//  Created by Yu Chen on 1/28/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#include <iostream>
#include "HexBoard.hpp"

using namespace std;

HexBoard::HexBoard(int side): N(side),V(side*side) {
    adj = new set<int>[V];
    for(int i=0; i<V; ++i) {
        int x = getX(i);
        int y = getY(i);
        int nx, ny;
        // six neighbors
        nx = x-1; ny = y;
        add_neighbor_safe(i, nx, ny);
        nx = x-1; ny = y+1;
        add_neighbor_safe(i, nx, ny);
        nx = x; ny = y-1;
        add_neighbor_safe(i, nx, ny);
        nx = x; ny = y+1;
        add_neighbor_safe(i, nx, ny);
        nx = x+1; ny = y-1;
        add_neighbor_safe(i, nx, ny);
        nx = x+1; ny = y;
        add_neighbor_safe(i, nx, ny);
    }
}

HexBoard::~HexBoard() {
    delete [] adj;
}

void HexBoard::print() {
    cout << "Adjacency List \n";
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
            cout << *it << ", ";
        cout << endl;
    }
}
