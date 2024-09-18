#include "hashable.hpp"
#include <cstdint>
#include <vector>

/**
 * White upper, black lower.
 * Ex. "Brnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR"
 */

bool operator==(CompressedBoard &left, CompressedBoard &right) {
    if (left.board_info_ != right.board_info_)
        return false;
    for (int i = 0; i < 16; i++) {
        if (left.chess_info_[i] != right.chess_info_[i])
            return false;
    }
    return true;
}
board expandBoard(CompressedBoard const & compressed_board) {
    vector<vector<chess *>> chessmap(8, vector<chess *>(8, nullptr));
    uint64_t bit = 1;
    int chessid = 0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (compressed_board.board_info_ & bit) {
                chessmap[x][y] = new chess {
                    point(x, y),
                    static_cast<bool>(compressed_board.chess_info_[chessid] & (1 << 3)),
                    chess_type(compressed_board.chess_info_[chessid] & 0b111)
                } ;
            }
            bit <<= 1;
        }
    }
    return board(chessmap, compressed_board.player_turns);
}
CompressedBoard compressBoard(vector<vector<chess*>> const & grid, bool turn) {
    CompressedBoard res;
    res.board_info_ = 0;
    for (int i = 0; i < 16; i++)
        res.chess_info_[i] = 0;
    uint64_t bit = 1;
    int chessid = 0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (!!grid[x][y]) {
                res.board_info_ |= bit;
                res.chess_info_[chessid++] =
                    grid[x][y]->c_type | (grid[x][y]->player << 3);
            }
            bit <<= 1;
        }
    }
    res.player_turns = turn;
    return res;
}
CompressedBoard compressBoard(board const &board) {
    CompressedBoard res;
    auto grid = board.get_grid();
    return compressBoard(grid, board.turns());
}
string boardToStr(vector<vector<chess *>> const &board, bool turn) {
    string res = "";
    if (turn == PLAYER_BLACK) {
        res += "B";
    } else {
        res += "W";
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]->c_type) {
                case KING:
                    if (board[i][j]->player == PLAYER_WHITE) {
                        res += "K";
                    } else {
                        res += "k";
                    }
                    break;
                case KNIGHT:
                    if (board[i][j]->player == PLAYER_WHITE) {
                        res += "N";
                    } else {
                        res += "n";
                    }
                    break;
                case QUEEN:
                    if (board[i][j]->player == PLAYER_WHITE) {
                        res += "Q";
                    } else {
                        res += "q";
                    }
                    break;
                case ROOK:
                    if (board[i][j]->player == PLAYER_WHITE) {
                        res += "R";
                    } else {
                        res += "r";
                    }
                    break;
                case BISHOP:
                    if (board[i][j]->player == PLAYER_WHITE) {
                        res += "B";
                    } else {
                        res += "b";
                    }
                    break;
                case PAWN:
                    if (board[i][j]->player == PLAYER_WHITE) {
                        res += "P";
                    } else {
                        res += "p";
                    }
                    break;
                default:
                    res += ".";
            }
        }
    }
    return res;
}

size_t normal_collision_handler(size_t index, size_t count, size_t size) {
    return (index + 1) % size;
}
// HashTable<int64_t, uint16_t, 0, normal_collision_handler> table(nullptr,
// nullptr);

int16_t combine_c_move(const chess_move &move) {
    int16_t result = 0;
    result |= (move.from.x & 0x0F) << 12;
    result |= (move.from.y & 0x0F) << 8;
    result |= (move.to.x & 0x0F) << 4;
    result |= (move.to.y & 0x0F);
    return result;
}

chess_move decode_c_move(int16_t combined) {
    chess_move move;
    move.from.x = (combined >> 12) & 0x0F;
    move.from.y = (combined >> 8) & 0x0F;
    move.to.x = (combined >> 4) & 0x0F;
    move.to.y = combined & 0x0F;
    return move;
}
