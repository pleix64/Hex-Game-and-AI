//
//  main.cpp
//  Hex_game
//
//  Created by Yu Chen on 1/28/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#include <iostream>
#include "HexBoard.hpp"
#include "GamePlay.hpp"

#include <deque>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

default_random_engine shfl_gen1(static_cast<unsigned>(time(0)));

int main(int argc, const char * argv[]) {
    
    // test fill and player_win
    /*
    HexBoard testBoard(11);
    set<int> empty_nodes;
    for(int i=0; i<testBoard.getV(); ++i)
        empty_nodes.insert(i);
    deque<int> mc_moves(empty_nodes.begin(),empty_nodes.end());
    shuffle(mc_moves.begin(), mc_moves.end(),shfl_gen1);
    //testBoard.fill(past_moves.begin(),past_moves.end());
    testBoard.fill(mc_moves.begin(),mc_moves.end()); //,current_color);
    testBoard.draw();
    if(testBoard.player_win(COLOR::BLUE))
        cout << "BLUE is winner.\n";
    else
        cout << "RED is winner.\n";
    */
    // test of game flow with drawing 
    GamePlay gp;
    gp.initialize();
    gp.game_flow();
    
    return 0;
}
