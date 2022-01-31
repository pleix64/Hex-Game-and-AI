//
//  HexBoard.cpp
//  hw4_Hex_basic
//
//  Created by Yu Chen on 1/28/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
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

HexBoard::HexBoard(int size): N(size),V(size*size) {
    col = vector<COLOR>(V,COLOR::WHITE);
    adj = new set<int>[V];
    //adj = new map<int,COLOR>[V];
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


int HexBoard::player_move(COLOR player, int x, int y) {
    if(player==COLOR::WHITE) {
        cout << "Player's color must be "
        "either COLOR::RED or COLOR::BLUE." << endl;
        return 2;
    }
    int i = getNode(x, y);
    // legal move
    if(x>=0 && x<N && y>=0 && y<N && col[i]==COLOR::WHITE)
        col[i] = player;
    else 
        return 1;
    
    // if neighbor is already with the same color
    // change the edge to this neighbor as the player's color
    // FIXME: it may turn out that no need for edge COLOR
    //for(auto it=adj[i].begin(); it!=adj[i].end(); ++it) {
    //    if(col[it->first]==player) {
    //        it->second = player;
    //        adj[it->first][i] = player;
    //    }
    //}
        
    // add this hexagon to player's open set
    int dist;
    if(player==COLOR::RED)
        dist = getX(i);
    else if(player==COLOR::BLUE)
        dist = getY(i);
    open[player].insert(make_pair(dist, i));
    
    return 0;
}

bool HexBoard::player_won(COLOR player) {
    bool won = false;
    // move player owned nodes (in open set) with coordinate 0
    // (x=0 for RED; y=0 for BLUE) to its closed set
    for(auto it=open[player].begin(); it!=open[player].end(); ) {
        if(it->first==0) {
            closed[player].insert(it->second);
            it = open[player].erase(it);
        }
        else
            break;
    }
    // move open set elements which are closed set elements' neighbors
    // to closed set
    auto it=open[player].begin();
    while(it!=open[player].end()) {
        //find_if(closed[player].begin(),closed[player].end(),
        //        bind(adjacent(_1, it->second)));
        auto it_adj =
        find_if(closed[player].begin(),closed[player].end(),
                [&](int x) {return this->adjacent(x, it->second);});
        if(it_adj!=closed[player].end()) {
            closed[player].insert(it->second);
            it = open[player].erase(it);
        }
        else
            ++it;
    }
    // player won if find any node with x=N-1 for RED
    // or y=N-1 for BLUE in closed set
    set<int>::iterator it_farside;
    if(player==COLOR::RED)
        it_farside = find_if(closed[player].begin(),closed[player].end(),
                            [&](int i){return this->getX(i)==N-1;});
    else if(player==COLOR::BLUE)
        it_farside = find_if(closed[player].begin(),closed[player].end(),
                            [&](int i){return this->getY(i)==N-1;});
    
    if(it_farside!=closed[player].end())
        won = true;
    
    return won;
}

void HexBoard::print() {
    cout << "Adjacency List \n";
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
            cout << (*it);
            if(col[*it]!=COLOR::WHITE)
                cout << "(" << col[*it] << ")";
            //cout << it->first;
            //if(it->second!=COLOR::WHITE)
            //    cout << "(" << it->second << ")";
            cout << ", ";
        }
        cout << endl;
    }
}

void HexBoard::draw() {
    string ws("  ");

    cout << " ";
    for(int y=0; y<N; y++) {
        cout << y << "   ";
    }
    cout << "\n";
    
    for(int x=0; x<N; x++) {
        for (int u=0;u<x;u++) cout << ws;
        cout << x;
        for(int y=0; y<N; y++) {
            int node = getNode(x, y);
            if(col[node]==COLOR::WHITE)
                cout << " . ";
            else if(col[node]==COLOR::RED)
                cout << " X ";
            else if(col[node]==COLOR::BLUE)
                cout << " O ";
            if(y!=N-1) cout << "-";
        }
        cout << "\n";
        
        if (x!=N-1) {
            cout << "   ";
            for (int u=0;u<x;u++) cout << ws;
            cout << "\\ ";
            for(int y=0; y<N-1; y++) {
                cout << "/ \\ ";
            }
            cout << "\n";
        }
     
    }
    
}
