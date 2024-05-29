
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"

class player {
protected:
    bool side;
public:
    player(bool side);
    virtual chess_move make_move(vector<vector<chess *>> const & state) = 0;
};

class ai_player: public player {
public:
    ai_player(bool side) : player(side) {}
    chess_move make_move(vector<vector<chess *>> const & state);
};

class terminal_player: public player {
public:
    terminal_player(bool side) : player(side) {}
    chess_move make_move(vector<vector<chess *>> const & state);
};

class remote_player: public player {
public:
    remote_player(bool side) : player(side) {}
    chess_move make_move(vector<vector<chess *>> const & state);

};

#endif