#ifndef CHESS_HPP
#define CHESS_HPP
#include <vector>

#define PLAYER_WHITE 0
#define PLAYER_BLACK 1

#include <stdint.h>
#include <unordered_set>

using namespace std;

/*
WHITE
    0   1   2   3   4   5   6   7   y
0   r   k   b   k   q   b   k   r
1   p   p   p   p   p   p   p   p
2
3
4
5
6   p   p   p   p   p   p   p   p
7   r   k   b   k   q   b   k   r
x
BLACK



*/

struct point {
    int16_t x: 8;
    int16_t y: 8; 
    bool operator==(const point &other) const
    { 
        return (*this).x == other.x && (*this).y == other.y;
    }
};

// Define knight directions as pairs of (x_change, y_change)

template <>
struct std::hash<point>
{
    std::size_t operator()(const point& k) const
    {
        return k.x << 8 + k.y;
    }
};

struct chess_move {
    point from;
    point to;
};

enum chess_type {
    KING    = 0, 
    QUEEN   = 1, 
    ROOK    = 2, 
    BISHOP  = 3, 
    KNIGHT  = 4, 
    PAWN    = 5,
};

struct chess {
    point pos;
    bool player;
    chess_type c_type;
    unordered_set<point> legal_move(vector<vector<chess *>> & board);
};

typedef unordered_set<point> (*move_func) (point pos, vector<vector<chess*>> & board);


unordered_set<point> pawn_legal_move   (point pos, vector<vector<chess*>> & board);
unordered_set<point> queen_legal_move  (point pos, vector<vector<chess*>> & board);
unordered_set<point> rook_legal_move   (point pos, vector<vector<chess*>> & board);
unordered_set<point> bishop_legal_move (point pos, vector<vector<chess*>> & board);
unordered_set<point> knight_legal_move (point pos, vector<vector<chess*>> & board);
unordered_set<point> king_legal_move   (point pos, vector<vector<chess*>> & board);


#endif