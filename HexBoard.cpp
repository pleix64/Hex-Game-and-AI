//
//  HexBoard.cpp
//  hw4_Hex_basic
//
//  Created by Yu Chen on 1/28/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#include <iostream>
#include <algorithm>
//#include <functional>
#include "HexBoard.hpp"

using namespace std;
//using namespace std::placeholders;

ostream& operator<<(ostream& out, const COLOR& color) {
    if(color==COLOR::RED)
        out << "RED";
    else if(color==COLOR::BLUE)
        out << "BLUE";
    else
        out << "WHIHE";
    return out;
}

HexBoard::HexBoard(int side): N(side),V(side*side) {
    col = vector<COLOR>(V,COLOR::WHITE);
    adj = new map<int,COLOR>[V];
    for(int i=0; i<V; ++i) {
        int x = getX(i);
        int y = getY(i);
        // six neighbors
        int nx, ny;
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

bool HexBoard::adjacent(int i, int j) {
    auto it = adj[i].find(j);
    return it!=adj[i].end();
}


void HexBoard::player_move(COLOR player, int x, int y) {
    if(player==COLOR::WHITE) {
        cout << "Player's color must be "
        "either COLOR::RED or COLOR::BLUE." << endl;
        return;
    }
    int i = getNode(x, y);
    // legal move
    if(x>=0 && x<N && y>=0 && y<N && col[i]==COLOR::WHITE)
        col[i] = player;
    else {
        cout << "Illegal move. \nPlease select an available location.\n";
        return;
    }
    
    // if neighbor is already with the same color
    // change the edge to this neighbor as the player's color
    // FIXME: it may turn out that no need for edge COLOR
    for(auto it=adj[i].begin(); it!=adj[i].end(); ++it) {
        if(col[it->first]==player) {
            it->second = player;
            adj[it->first][i] = player;
        }
    }
        
    // add this hexagon to player's open set
    int dist;
    if(player==COLOR::RED)
        dist = getX(i);
    else if(player==COLOR::BLUE)
        dist = getY(i);
    open[player].insert(make_pair(dist, i));
}

bool HexBoard::player_won(COLOR& player) {
    bool won = false;
    for(auto p:{COLOR::RED, COLOR::BLUE}){
        //add player owned nodes on North Side (RED) or West Side (BLUE)
        for(auto it=open[p].begin(); it!=open[p].end(); ) {
            if(it->first==0) {
                closed[p].insert(it->second);
                it = open[p].erase(it);
            }
            else
                break;
        }
        // move open set elements which are closed set elements' neighbors
        // to closed set
        auto it=open[p].begin();
        while(it!=open[p].end()) {
            //find_if(closed[p].begin(),closed[p].end(),
            //        bind(adjacent(_1, it->second)));
            auto it_adj =
            find_if(closed[p].begin(),closed[p].end(),
                    [&](int x) {return this->adjacent(x, it->second);});
            if(it_adj!=closed[p].end()) {
                closed[p].insert(it->second);
                it = open[p].erase(it);
            }
            else
                ++it;
        }
        // test whether one of players won
        set<int>::iterator it_farside;
        if(p==COLOR::RED)
            it_farside = find_if(closed[p].begin(),closed[p].end(),
                                 [&](int i){return this->getX(i)==N-1;});
        else if(p==COLOR::BLUE)
            it_farside = find_if(closed[p].begin(),closed[p].end(),
                                 [&](int i){return this->getY(i)==N-1;});
        
        if(it_farside!=closed[p].end()) {
            won = true;
            player = p;
        }
    }
    
    return won;
}

void HexBoard::print() {
    cout << "Adjacency List \n";
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
            cout << it->first;
            if(it->second!=COLOR::WHITE)
                cout << "(" << it->second << ")";
            cout << ", ";
        }
        cout << endl;
    }
}
