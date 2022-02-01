//
//  main.cpp
//  hw4_Hex_basic
//
//  Created by Yu Chen on 1/28/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#include <iostream>
#include "HexBoard.hpp"
#include "GamePlay.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    // test of game flow with drawing 
    GamePlay gp;
    gp.initialize();
    gp.game_flow();
    
    return 0;
}
