#ifndef BOARD_HPP
#define BOARD_HPP

#include "chess.hpp"
#include <vector>

/*
    KING    = 0, 
    QUEEN   = 1, 
    ROOK    = 2, 
    BISHOP  = 3, 
    KNIGHT  = 4, 
    PAWN    = 5,
*/

using namespace std;


class board {
    bool player_turns;
public:
    vector<vector<chess*>> grid;
    board();
    board(vector<vector<chess *>> & grid, bool player_turns);
    vector<vector<chess*>> get_grid() const {
        return grid;   
    }
    bool turns() const {
        return player_turns;
    }
    bool next_move(chess_move c_move);
    bool end();
    void print_board();
};

#endif
