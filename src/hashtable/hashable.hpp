#ifndef HASHABLE_BOARD_HPP
#define HASHABLE_BOARD_HPP

#include "../chess/chess.hpp"
#include "../chess/board.hpp"
#include "rpc/msgpack.hpp"

struct CompressedBoard {
    uint64_t board_info_;
    char chess_info_[16];
    bool player_turns;
    MSGPACK_DEFINE_ARRAY(board_info_, chess_info_, player_turns)
    inline void setChess(int index, char info) {
        info &= 0xf;
        chess_info_[index / 2] |= info << ((index % 2) == 1) * 4;
    }
};

bool operator == (CompressedBoard & left, CompressedBoard & right);
CompressedBoard compressBoard(board const & board);
CompressedBoard compressBoard(vector<vector<chess*>> const & board, bool turn);
board expandBoard(CompressedBoard const & board);
string boardToStr(vector<vector<chess*>> const & board, bool turn);
size_t normal_collision_handler(size_t index, size_t count, size_t size);
int16_t combine_c_move(const chess_move &move);
chess_move decode_c_move(int16_t combined);


#endif
