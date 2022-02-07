//
//  HexBoard.cpp
//  Hex_game
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
    if(color==COLOR::BLUE)
        out << "BLUE";
    else if(color==COLOR::RED)
        out << "RED";
    else
        out << "WHIHE";
    return out;
}
/*
void take_turns(COLOR& turn) {
    if(turn==COLOR::BLUE)
        turn = COLOR::RED;
    else if(turn==COLOR::RED)
        turn = COLOR::BLUE;
    else
        cout << "Error: current_turn is not properly initialized." << endl;
}
*/
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
/*
template <class InputIt>
void HexBoard::fill(InputIt first, InputIt last, COLOR curr) {
    if(curr==COLOR::WHITE) {
        cout << "Current color have to be either BLUE or RED.\n";
        return;
    }
    for (InputIt it=first; it!=last; ++it) {
        col[*it] = curr;
        take_turns(curr);
    }
}
*/
bool HexBoard::adjacent(int i, int j) {
    auto it = adj[i].find(j);
    return it!=adj[i].end();
}


int HexBoard::player_move(COLOR player, int node, bool swap_on) {
    if(player==COLOR::WHITE) {
        cout << "Player's color must be "
        "either COLOR::BLUE or COLOR::RED." << endl;
        return 2;
    }
    // legal move
    int x = getX(node);
    int y = getY(node);
    if(x>=0 && x<N && y>=0 && y<N) {
        if(col[node]==COLOR::WHITE || swap_on)
            col[node] = player;
        else
            return 1;
    }
    else 
        return 1;
    
    // add this hexagon to player's open set
    int dist;
    if(player==COLOR::BLUE)
        dist = getY(node);
    else if(player==COLOR::RED)
        dist = getX(node);
    open[player].insert(make_pair(dist, node));
    
    return 0;
}

bool HexBoard::player_won(COLOR player) {
    bool won = false;
    // move player owned nodes (in open set) with coordinate 0
    // (y=0 for BLUE; x=0 for RED) to its closed set
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
    // player won if find any node with y=N-1 for BLUE
    // or x=N-1 for RED in closed set
    set<int>::iterator it_farside;
    if(player==COLOR::BLUE)
        it_farside = find_if(closed[player].begin(),closed[player].end(),
                            [&](int i){return this->getY(i)==N-1;});
    else if(player==COLOR::RED)
        it_farside = find_if(closed[player].begin(),closed[player].end(),
                            [&](int i){return this->getX(i)==N-1;});
    
    if(it_farside!=closed[player].end())
        won = true;
    
    return won;
}

bool HexBoard::player_win(COLOR player) {
    set<pair<int,int>> _open;
    set<int> _closed;
    
    // Initialize open set and closed set
    // For player's associate coordinates (as y to BLUE)
    // go over another coordinate (like x)
    // with each node requiring player's coordinate==0 (one side)
    for(int another=0; another<N; ++another) {
        int node;
        if(player==COLOR::BLUE)
            node = getNode(another, 0);
        else
            node = getNode(0, another);
        
        if(col[node]==player) {
            _closed.insert(node);
            for(auto neighbor: adj[node]) {
                if(col[neighbor]==player && _closed.find(neighbor)==_closed.end())
                    _open.insert(make_pair(-getPlayerCoord(neighbor, player), neighbor));
            }
        }
    }
    
    bool win = false;
    while(!_open.empty() && !win) {
        int node = _open.begin()->second;
        _open.erase(_open.begin());
        _closed.insert(node);
        for(auto neighbor : adj[node]) {
            if(col[neighbor]==player && _closed.find(neighbor)==_closed.end())
                _open.insert(make_pair(-getPlayerCoord(neighbor, player), neighbor));
        }
        if(getPlayerCoord(node, player)==N-1)
            win = true;
    }
    
    return win;
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
            else if(col[node]==COLOR::BLUE)
                cout << " X ";
            else if(col[node]==COLOR::RED)
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
