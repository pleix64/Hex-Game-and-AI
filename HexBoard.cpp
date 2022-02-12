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
    
     return 0;
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
            cout << ", ";
        }
        cout << endl;
    }
}

void HexBoard::draw() {
    string ws("  ");
    string sws(" ");

    cout << " ";
    for(int y=0; y<N; y++) {
        cout << y << "   ";
    }
    cout << "\n";
    
    for(int x=0; x<N; x++) {
        for (int u=0;u<x;u++) {
            if(u<9) cout << ws;
            else cout << sws;
        }
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
