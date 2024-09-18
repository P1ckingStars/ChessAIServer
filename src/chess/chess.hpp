#ifndef CHESS_HPP
#define CHESS_HPP
#include <cstddef>
#include <cstdint>
#include <vector>

#define PLAYER_WHITE 0
#define PLAYER_BLACK 1

#include <stdint.h>
#include <iostream>
#include <unordered_set>

using namespace std;

#define MOVE(grid, c_move) { grid[c_move.to.x][c_move.to.y]      = grid[c_move.from.x][c_move.from.y];\
        grid[c_move.to.x][c_move.to.y]->pos = c_move.to;\
        grid[c_move.from.x][c_move.from.y]  = nullptr;\
        if ((c_move.to.x == 0 || c_move.to.x == 7) && grid[c_move.to.x][c_move.to.y]->c_type == PAWN) {\
            grid[c_move.to.x][c_move.to.y]->c_type = QUEEN;\
        }\
}
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
    int8_t x;
    int8_t y; 
    bool operator==(const point &other) const
    { 
        return (*this).x == other.x && (*this).y == other.y;
    }
    point(int8_t x, int8_t y) {
        this->x = x;
        this->y = y;
    }
    point() {}
    void print() {
        // cout << "point x: " << x << ", y: " << y;
    }
};

#define MAKE_POINT(x, y) ()

// Define knight directions as pairs of (x_change, y_change)

template <>
struct std::hash<point>
{
    std::size_t operator()(const point& k) const
    {
        return *(int16_t *)&k;
    }
};

struct chess_move {
    point from;
    point to;
    chess_move() {
        from.x = 0;
        from.y = 0;
        to.x = 0;
        to.y = 0;
    }
    chess_move(point from, point to) {
        this->from  = from;
        this->to    = to;
    }
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
    point       pos;
    bool        player;
    chess_type  c_type;
    int         mobility = 0; // size of legal_move (may times a constant)
    unordered_set<point> legal_move(vector<vector<chess *>> const & board);
    int mobility_score(vector<vector<chess *>> const & board, bool turns);
};

typedef unordered_set<point> (*move_func) (point pos, vector<vector<chess*>> const & board);

typedef int (*mobility_core_func) (point pos, vector<vector<chess*>> const & board, bool turns);

unordered_set<point> pawn_legal_move   (point pos, vector<vector<chess*>> const & board);
unordered_set<point> queen_legal_move  (point pos, vector<vector<chess*>> const & board);
unordered_set<point> rook_legal_move   (point pos, vector<vector<chess*>> const & board);
unordered_set<point> bishop_legal_move (point pos, vector<vector<chess*>> const & board);
unordered_set<point> knight_legal_move (point pos, vector<vector<chess*>> const & board);
unordered_set<point> king_legal_move   (point pos, vector<vector<chess*>> const & board);

// int pawn_mobility_score    (point pos, vector<vector<chess*>> const & board, bool turns);
// int queen_mobility_score   (point pos, vector<vector<chess*>> const & board, bool turns);
// int rook_mobility_score    (point pos, vector<vector<chess*>> const & board, bool turns);
// int bishop_mobility_score  (point pos, vector<vector<chess*>> const & board, bool turns);
// int knight_mobility_score  (point pos, vector<vector<chess*>> const & board, bool turns);
// int king_mobility_score    (point pos, vector<vector<chess*>> const & board, bool turns);

#endif
