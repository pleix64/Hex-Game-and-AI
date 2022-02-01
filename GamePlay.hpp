//
//  GamePlay.hpp
//  hw4_Hex_basic
//
//  Created by Yu Chen on 1/29/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#ifndef GamePlay_hpp
#define GamePlay_hpp

#include <iostream>
#include <random>
#include "HexBoard.hpp"

using namespace std;

class GamePlay{
public:
    GamePlay() {
        turns = vector<int>(2,0);
    }
    ~GamePlay() {
        
    }
    void initialize();
    void take_turns() {
        if(current_turn==COLOR::BLUE)
            current_turn = COLOR::RED;
        else if(current_turn==COLOR::RED)
            current_turn = COLOR::BLUE;
        else
            cout << "Error: current_turn is not properly initialized." << endl;
    }
    void game_flow();
    // control game flow according to settngs (game_mode and human_player)
    // basic loop:
    // if human, enter a hexagon coordinate from keyboard
    // if computer, generate a reasonable move
    // hex->player_move(current_turn, x, y);
    // if(hex->player_won(current_turn) ...;
    // take_turns();
    
    void generate_move(int&x, int&y);
    
private:
    COLOR current_turn;
    vector<int> turns; // num of turns for BLUE and RED respectively
    HexBoard * hex; // HexBoard that GamePlay talks to
    
    int board_size;
    int game_mode;
    int human_player; // Not apply to two computer or two human players cases
};

#endif /* GamePlay_hpp */
