#ifndef CHESS_HPP
#define CHESS_HPP
#include <vector>

#define PLAYER_WHITE 0
#define PLAYER_BLACK 1

using namespace std;

struct point {
    int x;
    int y; 
};

struct move {
    point from;
    point to;
};

enum chess_type {
    KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN
};

class chess {
    point pos;
    bool player;
    chess_type c_type;
    vector<point> legal_move();
};

vector<point> pawn_legal_move   (point pos);
vector<point> queen_legal_move  (point pos);
vector<point> rook_legal_move   (point pos);
vector<point> bishop_legal_move (point pos);
vector<point> knight_legal_move (point pos);
vector<point> king_legal_move   (point pos);


#endif