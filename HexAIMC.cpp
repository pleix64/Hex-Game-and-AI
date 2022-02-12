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

default_random_engine shfl_gen(static_cast<unsigned>(time(0))); // random engine for shuffle
default_random_engine uni_gen(static_cast<unsigned>(time(0)));
uniform_int_distribution<int> zeroone(0,1);
auto half = bind(zeroone,uni_gen); // functor to generate 0 or 1 with a half/half probability

int HexAIMC::best_move(int opp_last) {
    
    if(ai_color!=COLOR::WHITE && opp_last>=0) {
        past_moves.push_back(opp_last);
        empty_nodes.erase(opp_last);
    }
    
    vector<int> wins(V,0), total(V,0); // wins and total count on each node for next move
    deque<int> mc_moves(empty_nodes.begin(),empty_nodes.end());
    for(int i=0; i<num_trials*empty_nodes.size(); ++i) {
        shuffle(mc_moves.begin(), mc_moves.end(),shfl_gen);
        
        bool swapped = false;
        if(past_moves.size()==0 && half()==1) {
            int first_move = mc_moves.front();
            mc_moves.push_front(first_move);
            swapped = true;
        }
        if(past_moves.size()==1 && half()==1) {
            int first_move = past_moves.back();
            mc_moves.push_front(first_move);
            swapped = true;
        }

        sim->fill(past_moves.begin(),past_moves.end());
        sim->fill(mc_moves.begin(),mc_moves.end(),current_color);
        
        if(sim->player_win(current_color))
            wins[mc_moves.front()]++;
        total[mc_moves.front()]++;
        
        if(swapped)
            mc_moves.pop_front();
    }
  
    //cout << "WLR: ";
    set<pair<double, int>> WLR; // Win-Loss Rate is defined as wins/(wins+loss)
    for(int i=0; i<V; ++i) {
        double wlr = total[i]==0 ? 0.0 : static_cast<double>(wins[i])/total[i];
        WLR.insert(make_pair(-1* wlr, i));
        //cout << wlr << ", ";
    }
    //cout << endl;

    int best = WLR.begin()->second;
    past_moves.push_back(best);
    empty_nodes.erase(best);
    if(ai_color==COLOR::WHITE)
        take_turns(current_color);
    
    return best;
}
