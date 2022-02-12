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
    // 
    
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
