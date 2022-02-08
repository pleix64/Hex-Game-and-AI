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
    
    /*
    HexBoard hb(9);
    
    int n = hb.getNode(5, 3);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(4, 5);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(3, 5);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(3, 7);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";

    n = hb.getNode(3, 6);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";

    n = hb.getNode(2, 7);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(4, 6);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(4, 8);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(4, 7);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(3, 8);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(5, 7);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(5, 8);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(6, 7);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(6, 8);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(7, 7);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(7, 8);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(8, 8);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(8, 7);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";

    n = hb.getNode(1, 7);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(2, 6);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(1, 6);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(2, 5);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(1, 5);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(3, 4);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(1, 8);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(3, 3);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(2, 4);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(3, 2);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(2, 3);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(2, 2);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "winner.\n";
    
    n = hb.getNode(1, 3);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(1, 2);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    n = hb.getNode(0, 3);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    n = hb.getNode(0, 1);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "winner.\n";
    
    n = hb.getNode(0, 0);
    hb.player_move(COLOR::BLUE, n);
    if(hb.player_win(COLOR::BLUE))
        cout << "winner.\n";
    
    // key moment
    n = hb.getNode(0, 2);
    hb.player_move(COLOR::RED, n);
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
    
    //n = hb.getNode(1, 1);
    //hb.player_move(COLOR::BLUE, n);
    
    //n = hb.getNode(1, 0);
    //hb.player_move(COLOR::RED, n);
    
    hb.draw();
    if(hb.player_win(COLOR::RED))
        cout << "RED is winner.\n";
*/
    
    return 0;
}
