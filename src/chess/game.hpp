#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "player.hpp"

class game {
    board m_board;
    player *p_black;
    player *p_white;
public:
    game();
    game(player * black, player * white): p_black(black), p_white(white), m_board(board()) {}
    void run();
};



#endif
