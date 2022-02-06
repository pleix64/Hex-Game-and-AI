//
//  HexAIMC.hpp
//  hw5_Hex_game
//
//  Created by Yu Chen on 2/5/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#ifndef HexAIMC_hpp
#define HexAIMC_hpp

#include <iostream>
#include <vector>
#include <set>
#include "HexBoard.hpp"

using namespace std;

const int num_trials = 1000;

class HexAIMC {
public:
    HexAIMC(HexBoard *pHB, COLOR AI_color);
    HexAIMC(HexBoard *pHB):HexAIMC(pHB, COLOR::WHITE) {
        // use this constructor to let AI plays for both side
    }
    ~HexAIMC();
    
    int best_move(int opp_last);
    // the evaluation of best move
    // what you need to do is for every turn,
    // given current color and opponent's last move,
    // simulate the rest of game for every available move for 1000 times,
    // and estimate each win-loss rate (or loss-win rate since the ordering
    // is by default ascending)
    //
    // past_moves and empty_nodes keep track of the actual game state
    // 
    
private:
    const COLOR ai_color; // the color AI plays for.
                          // WHITE means playing for both sides
    COLOR current_color; // FIXME: figure out whether really need this
    // the actual color that takes turns if play for both sides
    int V; // number of Hex board nodes
    vector<int> past_moves;
    set<int> empty_nodes; // booking the available nodes
    HexBoard* hex; // the HexBoard that AI plays on
    HexBoard* sim; // the HexBoard used for Monte Carlo simulations
};

#endif /* HexAIMC_hpp */
