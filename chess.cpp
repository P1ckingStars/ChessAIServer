#include "chess.hpp"
/*
    KING    = 0, 
    QUEEN   = 1, 
    ROOK    = 2, 
    BISHOP  = 3, 
    KNIGHT  = 4, 
    PAWN    = 5,
*/
using namespace std;

point knight_directions[8] = {
    {2, 1},   // Move 2 squares right, 1 square up
    {2, -1},  // Move 2 squares right, 1 square down
    {-2, 1},  // Move 2 squares left, 1 square up
    {-2, -1}, // Move 2 squares left, 1 square down
    {1, 2},   // Move 1 square right, 2 squares up
    {1, -2},  // Move 1 square right, 2 squares down
    {-1, 2},  // Move 1 square left, 2 squares up
    {-1, -2}  // Move 1 square left, 2 squares down
};
move_func chess_move[6] = {
    king_legal_move     ,
    queen_legal_move    ,
    rook_legal_move     ,
    bishop_legal_move   ,
    knight_legal_move   ,
    pawn_legal_move   
};

bool inline is_in_board(int x, int y){
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

enum dir_displacement {
    STAY    = 0,
    PLUS    = 1,
    MINUS   = -1
};

void move_dir(point pos, vector<vector<chess*>> & board, unordered_set<point> &res, dir_displacement dir_x, dir_displacement dir_y) {
    point start = pos;
    start.print();
    while (start.x >= 0 && start.x < 8 && start.y >= 0 && start.y < 8){
        start.x += dir_x;
        start.y += dir_y;
        if (!is_in_board(start.x, start.y)) return;
        if (board[start.x][start.y] == nullptr){
            res.insert(start);
            start.print();
        }
        else {
            if (board[start.x][start.y]->player != board[pos.x][pos.y]->player) {
                res.insert(start);
                start.print();
                break;
            }
            if (board[start.x][start.y]->player == board[pos.x][pos.y]->player) {
                break;
            }
        }
    }
}

void move_right(point pos, vector<vector<chess*>> & board, unordered_set<point> &res){
    move_dir(pos, board, res, STAY, PLUS);
}

void move_left(point pos, vector<vector<chess*>> & board, unordered_set<point> &res){
    move_dir(pos, board, res, STAY, MINUS);
}

void move_up(point pos, vector<vector<chess*>> & board, unordered_set<point> &res){
    move_dir(pos, board, res, MINUS, STAY);
}

void move_down(point pos, vector<vector<chess*>> & board, unordered_set<point> &res){
    move_dir(pos, board, res, PLUS, STAY);
}

void move_up_right(point pos, vector<vector<chess*>> & board, unordered_set<point> &res){
    move_dir(pos, board, res, MINUS, PLUS);
}

void move_up_left(point pos, vector<vector<chess*>> & board, unordered_set<point> &res){
    move_dir(pos, board, res, MINUS, MINUS);
}

void move_down_right(point pos, vector<vector<chess*>> & board, unordered_set<point> &res){
    move_dir(pos, board, res, PLUS, PLUS);
}

void move_down_left(point pos, vector<vector<chess*>> & board, unordered_set<point> &res){
    move_dir(pos, board, res, PLUS, MINUS);
}

unordered_set<point> pawn_legal_move(point pos, vector<vector<chess*>> & board){
    unordered_set<point> res;

    // current player white
    if (board[pos.x][pos.y]->player == PLAYER_WHITE){
        // white pawn at init pos forward move (1)
        if (pos.x == 1){
            if (board[3][pos.y] == nullptr){
                res.insert({3, pos.y});
            }
        }
        if (pos.x < 7){
            // forward move (2)
            if (board[pos.x + 1][pos.y] == nullptr){
                res.insert({(int8_t)(pos.x + 1), pos.y});
            }

            // diagonal capture left (3) & right (4)
            if (is_in_board(pos.x + 1, pos.y - 1) && board[pos.x + 1][pos.y - 1] && board[pos.x + 1][pos.y - 1]->player == PLAYER_BLACK){
                res.insert({(int8_t)(pos.x + 1), (int8_t)(pos.y - 1)});
            }
            if (is_in_board(pos.x + 1, pos.y + 1) && board[pos.x + 1][pos.y + 1] && board[pos.x + 1][pos.y + 1]->player == PLAYER_BLACK){
                res.insert({(int8_t)(pos.x + 1), (int8_t)(pos.y + 1)});
            }
        }
    }

    // current player black
    if (board[pos.x][pos.y]->player == PLAYER_BLACK){
        // black pawn at init pos forward move (1)
        if (pos.x == 6){
            if (board[4][pos.y] == nullptr){
                res.insert({4, pos.y});
            }
        }
        if (pos.x > 0){
            // forward move (2)
            if (board[pos.x - 1][pos.y] == nullptr){
                res.insert({(int8_t)(pos.x - 1), pos.y});
            }

            // diagonal capture left (3) & right (4)
            if (is_in_board(pos.x - 1, pos.y - 1) && board[pos.x - 1][pos.y - 1] && board[pos.x - 1][pos.y - 1]->player == PLAYER_WHITE){
                res.insert({(int8_t)(pos.x - 1), (int8_t)(pos.y - 1)});
            }
            if (is_in_board(pos.x - 1, pos.y + 1) && board[pos.x - 1][pos.y + 1] && board[pos.x - 1][pos.y + 1]->player == PLAYER_WHITE){
                res.insert({(int8_t)(pos.x - 1), (int8_t)(pos.y + 1)});
            }
        }
    }
    return res;
}

unordered_set<point> queen_legal_move  (point pos, vector<vector<chess*>> & board){
    unordered_set<point> res;

    // diagonal move
    move_up_left(pos, board, res);
    move_down_right(pos, board, res);
    move_down_left(pos, board, res);
    move_up_right(pos, board, res);

    move_up(pos, board, res);
    move_down(pos, board, res);
    move_left(pos, board, res);
    move_right(pos, board, res);
    return res;
}

unordered_set<point> rook_legal_move   (point pos, vector<vector<chess*>> & board){
    unordered_set<point> res;
    cout << "rook legal moves:" << endl; 
    move_up(pos, board, res);
    move_down(pos, board, res);
    move_left(pos, board, res);
    move_right(pos, board, res);
    return res;
}

unordered_set<point> bishop_legal_move(point pos, vector<vector<chess *>> &board){
    unordered_set<point> res;
    // diagonal move
    move_up_left(pos, board, res);
    move_down_right(pos, board, res);
    move_down_left(pos, board, res);
    move_up_right(pos, board, res);
    return res;
}

unordered_set<point> knight_legal_move(point pos, vector<vector<chess *>> &board){
    unordered_set<point> legal_moves;

    for (const auto &direction : knight_directions) {
        int next_x = pos.x + direction.x;
        int next_y = pos.y + direction.y;

        if (is_in_board(next_x, next_y)) {
            chess* dest = board[next_x][next_y];
            if (dest == nullptr || dest->player != board[pos.x][pos.y]->player) {
                legal_moves.insert({static_cast<int16_t>(next_x), static_cast<int16_t>(next_y)});
            }
        }
    }
    return legal_moves;
}

unordered_set<point> king_legal_move(point pos, vector<vector<chess *>> &board){
    unordered_set<point> res;
    if (pos.x > 0){
        if (board[pos.x - 1][pos.y] == nullptr){
            res.insert({(int8_t)(pos.x - 1), pos.y});
        } else {
            if (board[pos.x - 1][pos.y]->player != board[pos.x][pos.y]->player){
                res.insert({(int8_t)(pos.x - 1), pos.y});
            }
        }
    }
    if (pos.x < 7){
        if (board[pos.x + 1][pos.y] == nullptr){
            res.insert({(int8_t)(pos.x + 1), pos.y});
        } else {
            if (board[pos.x + 1][pos.y]->player != board[pos.x][pos.y]->player){
                res.insert({(int8_t)(pos.x + 1), pos.y});
            }
        }
    }
    if (pos.y > 0){
        if (board[pos.x][pos.y - 1] == nullptr){
            res.insert({pos.x, (int8_t)(pos.y - 1)});
        } else {
            if (board[pos.x][pos.y - 1]->player != board[pos.x][pos.y]->player){
                res.insert({pos.x, (int8_t)(pos.y - 1)});
            }
        }
    }
    if (pos.y < 7){
        if (board[pos.x][pos.y + 1] == nullptr){
            res.insert({pos.x, (int8_t)(pos.y + 1)});
        } else {
            if (board[pos.x][pos.y + 1]->player != board[pos.x][pos.y]->player){
                res.insert({pos.x, (int8_t)(pos.y + 1)});
            }
        }
    }
    return res;
}

unordered_set<point> chess::legal_move(vector<vector<chess *>> & board) {
    return chess_move[this->c_type](this->pos, board);
}