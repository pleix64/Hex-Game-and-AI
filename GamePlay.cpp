//
//  GamePlay.cpp
//  hw4_Hex_basic
//
//  Created by Yu Chen on 1/29/22.
//  Copyright © 2022 Yu Chen. All rights reserved.
//

#include <ctime>
#include "GamePlay.hpp"

using namespace std;

void GamePlay::initialize() {
    // enter data from keyboard
    board_size = 11;
    cout << "Welcome to Hex! \n";
    cout << "Enter board size (press enter for default value 11): ";
    if(cin.peek()!='\n')
        cin >> board_size;
    // FIXME: need to learn cin.ignore() in detail
    // Right now, OK for just press enter,
    // but doesn't work in case of entering whitespaces then enter key
    // Then, found cin.ignore is needed to ensure the next entered content
    // won't be treated as Enter Key
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //cout << "test: board size is " << board_size << endl;
    
    game_mode = 1;
    cout << "Game mode: \n";
    cout << "   (1) Human vs Computer;\n";
    cout << "   (2) Human vs Human;\n";
    cout << "   (3) Computer vs Computer.\n";
    cout << "Choose game mode: ";
    if(cin.peek()!='\n')
        cin >> game_mode;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(game_mode!=1 && game_mode!=2 && game_mode!=3) {
        cout << "Enter a valid number: ";
        if(cin.peek()!='\n')
            cin >> game_mode;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //cout << "test: game mode is set to " << game_mode << endl;
    
    human_player = 1;
    cout << "Player 1 (RED) goes first, then Player 2 (BLUE).\n";
    if(game_mode==1) { // H vs C
        cout << "Choose your player (enter 1 or 2):";
        if(cin.peek()!='\n')
            cin >> human_player;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while(human_player!=1 && human_player!=2) {
            cout << "Enter a valid number (1 or 2): ";
            if(cin.peek()!='\n')
                cin >> human_player;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
    if(game_mode==1) {
        if(human_player==1)
            cout << "You play RED and go first.\n";
        else
            cout << "You play BLUE. Computer goes first.\n";
    }
    else if(game_mode==2)
        cout << "Two human players take turns.\n";
    else
        cout << "Two computer players take turns (simulation mode).\n";
    
    // set up game
    hex = new HexBoard(board_size);
    current_turn = COLOR::RED;
    hex->draw();
}

void GamePlay::game_flow() {
    // control game flow according to settngs (game_mode and human_player)
    // basic loop:
    // if human, enter a hexagon coordinate from keyboard
    // if computer, generate a reasonable move
    // make a move, and check its validity
    // check if current player has won
    // draw the Hex board
    // take_turns();
    
    bool P1_is_human = false, P2_is_human = false;
    if(game_mode==1) {
        if(human_player==1) {
            P1_is_human = true;
            P2_is_human = false;
        }
        else {
            P1_is_human = false;
            P2_is_human = true;
        }
    }
    else if(game_mode==2) {
        P1_is_human = P2_is_human = true;
    }
    else if(game_mode==3) {
        P1_is_human = P2_is_human = false;
    }
    else
        cout << "Error: wrong game mode. This message should never be printed.\n";

    bool won = false;
    COLOR winner;
    while(!won) {
        // determine whether wait for keyboard input or generate from AI
        bool human_play_now = false;
        if(current_turn==COLOR::RED) {
            if(P1_is_human)
                human_play_now = true;
            else
                human_play_now = false;
        }
        else if (current_turn==COLOR::BLUE) {
            if(P2_is_human)
                human_play_now = true;
            else
                human_play_now = false;
        }
        
        bool valid_input = true;
        do{
            // keyboard input for human player,
            // or move generator for computer player
            int x,y;
            if(human_play_now){
                cout << "Player " << int(current_turn) << ", Enter your move (x y):";
                cin >> x >> y;
            }
            else {
                if(valid_input)
                    cout << "Player " << int(current_turn) << " move:\n";
                generate_move(x, y);
            }
            // validate the move
            if(hex->player_move(current_turn, x, y)) {
                valid_input = false;
                if(human_play_now)
                    cout << "Illegal move. \nPlease select an available location.\n";
            }
            else
                valid_input = true;
        }while(!valid_input);
        
        won = hex->player_won(current_turn);
        if(won) winner = current_turn;
        if(current_turn==COLOR::RED)
            turns[0]++;
        else
            turns[1]++;
        
        hex->draw();
        take_turns();
    }
    
    cout << "Winner is " << winner << ".\n";
    cout << "Total turns: " << (turns[0]+turns[1]);
    cout << " (RED " << turns[0] << ", BLUE " << turns[1] << ").\n";
    
}

default_random_engine rand_gen(static_cast<unsigned>(time(0)));

void GamePlay::generate_move(int&x, int&y) {
    // tyr a trivial simple strategy first--random
    uniform_int_distribution<int> coord(0,board_size-1);
    x = coord(rand_gen);
    y = coord(rand_gen);
}
