//
//  main.cpp
//  hw4_Hex_basic
//
//  Created by Yu Chen on 1/28/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#include <iostream>
#include "HexBoard.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    HexBoard HB(5);
    HB.print();
    cout << endl;
    COLOR winner;
    HB.player_move(COLOR::RED, 2, 2);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::BLUE, 3, 1);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::RED, 3, 2);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::BLUE, 3, 0);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::RED, 0, 3);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::BLUE, 1, 2);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::RED, 1, 3);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::BLUE, 4, 2);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.player_move(COLOR::RED, 4, 1);
    if(HB.player_won(winner))
        cout << "Winner is " << winner << endl;
    else cout << "No winner yet" << endl;
    HB.print();
    
    // test illegal moves
    //HB.player_move(COLOR::BLUE, -2, 4);
    //HB.print();

    return 0;
}
