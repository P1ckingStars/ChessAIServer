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
    void run();
};



#endif
