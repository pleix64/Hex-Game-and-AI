//
//  HexAIMC.cpp
//  hw5_Hex_game
//
//  Created by Yu Chen on 2/5/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#include <random>
#include <algorithm>
#include <vector>
#include <deque>

#include "HexAIMC.hpp"

HexAIMC::HexAIMC(HexBoard *pHB, COLOR AI_color): hex(pHB),ai_color(AI_color) {
    V = hex->getV();
    for(int i=0; i<V; ++i)
        empty_nodes.insert(i);
    sim = new HexBoard(hex->getN());
    
    if(ai_color==COLOR::WHITE) // play for both sides
        current_color = COLOR::BLUE; // initialized to be player 1
    else
        current_color = ai_color;
}

HexAIMC::~HexAIMC() {
    delete sim;
}

default_random_engine shfl_gen(static_cast<unsigned>(time(0)));

int HexAIMC::best_move(int opp_last) {
    
    if(ai_color!=COLOR::WHITE) {
        past_moves.push_back(opp_last);
        empty_nodes.erase(opp_last);
    }
    
    vector<int> wins(V,0), total(V,0); // wins and total count on each node for next move
    deque<int> mc_moves(empty_nodes.begin(),empty_nodes.end());
    for(int i=0; i<num_trials*empty_nodes.size(); ++i) {
        // FIXME:: add pie rule move later
        shuffle(mc_moves.begin(), mc_moves.end(),shfl_gen);
        sim->fill(past_moves.begin(),past_moves.end());
        sim->fill(mc_moves.begin(),mc_moves.end(),current_color);
        //sim->draw(); // test board fill
        if(sim->player_win(current_color))
            wins[mc_moves[0]]++;
        total[mc_moves[0]]++;
        // FIXME: consider whether need to reset sim to all WHITE here
        // in principle no need, but worth to check if everything works correctly
        // maybe use small board to test first.
    }
    
    set<pair<double, int>> WLR; // Win-Loss Rate is defined as wins/(wins+loss)
    for(int i=0; i<V; ++i)
        WLR.insert(make_pair(-1* static_cast<double>(wins[i]/total[i]), i));
    
    int best = WLR.begin()->second;
    
    if(ai_color==COLOR::WHITE) {
        past_moves.push_back(best);
        empty_nodes.erase(best);
        // need to flip color (maybe this should be a utility function-->FIXME:)

    }
    
    return best;
}
