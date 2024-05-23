#ifndef BOARD_HPP
#define BOARD_HPP

#include "chess.hpp"
#include <vector>
#define PLAYER_A 0
#define PLAYER_B 1

using namespace std;

class board {
    vector<vector<chess>> grid;
public:
    vector<vector<chess>> get_grid();
    bool next_move(int from_x, int from_y, int to_x, int to_y);
    bool turns();
    bool end();
};

#endif