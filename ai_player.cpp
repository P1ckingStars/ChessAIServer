#include "player.hpp"
#include "chess.hpp"
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

vector<int> piece_values = {50000, 10000, 1000, 700, 550, 100};

static int minimax = 0;

int utility(vector<vector<chess *>> const &board) {
    int score = 0;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            chess* piece = board[i][j];
            if (piece) {
                if (piece->player == PLAYER_WHITE) score += piece_values[piece->c_type];
                else score -= piece_values[piece->c_type];
            }
        }
    }

    return score;
}

int get_min(vector<vector<chess *>> &board, int depth, int alpha, int beta){
    int min_eval = INT_MAX;
    vector<vector<chess *>> temp;
    // action
    for (int16_t i = 0; i < 8; i++){
        for (int16_t j = 0; j < 8; j++){
            if (board[i][j] && board[i][j]->player == PLAYER_BLACK){
                board[i][j]->legal_move(board);
            }
        }
    }

    for (const auto &move : possible_moves) {
        int eval = minimax(__ , depth - 1, true, alpha, beta);
        min_eval = std::min(min_eval, eval);
        beta = std::min(beta, eval);

        if (beta <= alpha)
            break;
    }

    return min_eval;

}

int get_max(vector<vector<chess *>> &board, int depth, int alpha, int beta){
    int max_eval = INT_MIN;
    vector<vector<chess *>> temp;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] && board[i][j]->player == PLAYER_WHITE){
                
            }
        }
    }

    for (const auto &move : possible_moves) {
        int eval = minimax(__, depth - 1, false, alpha, beta);
        max_eval = std::max(max_eval, eval);
        alpha = std::max(alpha, eval);

        if (beta <= alpha)
            break;
    }

    return max_eval;
}

int minimax(vector<vector<chess *>> &board, int depth, bool maximizing, int alpha, int beta) {
    if (depth == 0) return utility(board);
    if (maximizing){
        return get_max(board, depth, alpha, beta);
    } else {
        return get_min(board, depth, alpha, beta);
    }
}

chess_move ai_player::make_move(vector<vector<chess *>> const &state)
{
    
}
