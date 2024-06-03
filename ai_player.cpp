#include "player.hpp"
#include "chess.hpp"
#include <unordered_map>
#include <unordered_set>
#include <climits>

#define DEPTH   6

using namespace std;

vector<int> piece_values = {50000, 10000, 1000, 700, 550, 100};

struct best_move {
    int val;
    chess_move next_mv;
};

best_move minimax(vector<vector<chess *>> &board, int depth, bool maximizing, int alpha, int beta);

int utility(vector<vector<chess *>> const &board)
{
    int score = 0;
    int white_mobile = 0;
    int black_mobile = 0;
    int white_king = 0;
    int black_king = 0;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            chess *piece = board[i][j];
            if (piece)
            {
                if (piece->player == PLAYER_WHITE)
                    score += piece_values[piece->c_type];
                else
                    score -= piece_values[piece->c_type];

                // Mobility evaluation
                unordered_set<point> moves = piece->legal_move(board);
                if (piece->player == PLAYER_WHITE) 
                    white_mobile += moves.size();
                else 
                    black_mobile += moves.size();

                // King Safety
                if (piece->c_type == KING) {
                    if (piece->player == PLAYER_WHITE) 
                        white_king += (i < 2) ? 50 : 0;
                    else 
                        black_king += (i > 5) ? 50 : 0;
                }
            }
        }
    }

    score += white_mobile - black_mobile;
    score += white_king - black_king;

    return score;
}

best_move get_min(vector<vector<chess *>> &board, int depth, int alpha, int beta)
{
    if (depth <= 0) return {utility(board), {}};
    int min_eval = INT_MAX;
    vector<vector<chess *>> temp;
    // action
    vector<chess_move> possible_moves;
    for (int16_t i = 0; i < 8; i++)
    {
        for (int16_t j = 0; j < 8; j++)
        {
            if (board[i][j] && board[i][j]->player == PLAYER_BLACK)
            {
                if (!(board[i][j]->pos == point { i, j })) {
                cout << "position error at " << i << " " << j << endl;
                }
                for (auto &move : board[i][j]->legal_move(board)){
                    chess_move mv({i, j}, move);
                    possible_moves.push_back(mv);
                }
            }
        }
    }

    chess_move best = possible_moves[0];
    for (const auto &move : possible_moves)
    {
        chess *dest_piece = board[move.to.x][move.to.y];
        board[move.to.x][move.to.y]         = board[move.from.x][move.from.y];
        board[move.to.x][move.to.y]->pos    = move.to;
        board[move.from.x][move.from.y]     = nullptr;

        int eval = minimax(board, depth - 1, true, alpha, beta).val;

        board[move.from.x][move.from.y]         = board[move.to.x][move.to.y];
        board[move.from.x][move.from.y]->pos    = move.from;
        board[move.to.x][move.to.y]             = dest_piece;

        if (min_eval > eval){
            min_eval = eval;
            best = move;
        }

        beta = std::min(beta, eval);

        if (beta <= alpha)
            break;
    }

    return {min_eval, best};
}

best_move get_max(vector<vector<chess *>> &board, int depth, int alpha, int beta)
{
    if (depth <= 0) return {utility(board), {}};
    int max_eval = INT_MIN;
    vector<vector<chess *>> temp;
    // action
    vector<chess_move> possible_moves;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] && board[i][j]->player == PLAYER_WHITE){
                for (auto &move : board[i][j]->legal_move(board)){
                    chess_move mv({i, j}, move);
                    possible_moves.push_back(mv);
                }
            }
        }
    }

    chess_move best = possible_moves[0];
    for (const auto &move : possible_moves)
    {
        chess* dest_piece = board[move.to.x][move.to.y];
        board[move.to.x][move.to.y]         = board[move.from.x][move.from.y];
        board[move.to.x][move.to.y]->pos    = move.to;
        board[move.from.x][move.from.y]     = nullptr;

        int eval = minimax(board, depth - 1, false, alpha, beta).val;

        board[move.from.x][move.from.y]         = board[move.to.x][move.to.y];
        board[move.from.x][move.from.y]->pos    = move.from;
        board[move.to.x][move.to.y]             = dest_piece;
        
        if (max_eval < eval){
            max_eval = eval;
            best = move;
        }
        alpha = std::max(alpha, eval);

        if (beta <= alpha)
            break;
    }

    return {max_eval, best};
}

best_move minimax(vector<vector<chess *>> &board, int depth, bool maximizing, int alpha, int beta)
{
    if (depth == 0)
        return {utility(board), {}};
    if (maximizing)
        return get_max(board, depth, alpha, beta);
    else
        return get_min(board, depth, alpha, beta);
}

chess_move ai_player::make_move(vector<vector<chess *>> const &state) {
    vector<vector<chess *>> temp = state;
    return minimax(temp, DEPTH, !this->side, INT_MIN, INT_MAX).next_mv;
}


