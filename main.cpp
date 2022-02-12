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
    
    GamePlay gp;
    gp.initialize();
    gp.game_flow();
    
    return 0;
}
