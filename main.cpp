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
    
    /* test for board basic, legal move, and winning judgement
    HexBoard HB(5);
    HB.print();
    cout << endl;
    HB.player_move(COLOR::RED, 2, 2);
    if(HB.player_won(COLOR::RED))
        cout << "Winner is " << COLOR::RED << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::BLUE, 3, 1);
    if(HB.player_won(COLOR::BLUE))
        cout << "Winner is " << COLOR::BLUE << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::RED, 3, 2);
    if(HB.player_won(COLOR::RED))
        cout << "Winner is " << COLOR::RED << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::BLUE, 3, 0);
    if(HB.player_won(COLOR::BLUE))
        cout << "Winner is " << COLOR::BLUE << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::RED, 0, 3);
    if(HB.player_won(COLOR::RED))
        cout << "Winner is " << COLOR::RED << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::BLUE, 1, 2);
    if(HB.player_won(COLOR::BLUE))
        cout << "Winner is " << COLOR::BLUE << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::RED, 1, 3);
    if(HB.player_won(COLOR::RED))
        cout << "Winner is " << COLOR::RED << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::BLUE, 4, 2);
    if(HB.player_won(COLOR::BLUE))
        cout << "Winner is " << COLOR::BLUE << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::RED, 4, 1);
    if(HB.player_won(COLOR::RED))
        cout << "Winner is " << COLOR::RED << endl;
    else cout << "No winner yet" << endl;
    HB.print();
     */
    
    // test illegal moves
    //HB.player_move(COLOR::BLUE, -2, 4);
    //HB.print();

    return 0;
}
