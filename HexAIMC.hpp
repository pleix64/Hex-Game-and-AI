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
    // Use Monte Carlo method to evaluate the best move
    // Argument: the opponent last move
    // Pass a negative int if there is no opponent last move
    // (when evaluating the first move of the game)
    // It samples the sequence of nodes as the moves of
    // the rest course of a game from the current move to the end,
    // then calculate the win-loss-rate (WLR) of each different
    // available node for the current move. It picks the node
    // with the largest WLR to be the best choice of current move.
    // The algorithm is extended to include the swap rule (pie rule) case.
    // It can decide a reasonable first move when AI goes first
    // (avoid from being too good to be taken over by opponent),
    // and can decide whether to take over the first move node when AI goes second.
    
private:
    const COLOR ai_color; // the color AI plays for. WHITE means playing for both sides
    COLOR current_color; // the actual color that takes turns if play for both sides
    int V; // number of Hex board nodes
    vector<int> past_moves;
    set<int> empty_nodes; // the available nodes
    HexBoard* hex; // the HexBoard that AI plays on
    HexBoard* sim; // the HexBoard used for Monte Carlo simulations
};

#endif /* HexAIMC_hpp */
