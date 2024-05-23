
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"

class player {
    virtual move make_move(vector<vector<chess>> &state) = 0;
};

class ai_player: player {
    move make_move(vector<vector<chess>> &state);
}

class terminal_player: player {
    move make_move(vector<vector<chess>> &state);
}