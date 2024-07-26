#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <unordered_map>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "chess.hpp"
#include "../memoryallocator/allocator.h"

using namespace std;

typedef size_t(* CollisionHandler)(size_t index, size_t collision_count, size_t size);


template <class K, class V, V EmptyVal, CollisionHandler handler>
class HashTable {
    typedef int (* HashFunc)(K key);
protected:
    size_t size_;
    V * table_;
    Allocator * allocator_;
    HashFunc * hash_func_;
public:
    HashTable(Allocator * allocator, HashFunc * func) : allocator_(allocator), hash_func_(func) {}
    void put(int hash, V val) {

    }
    V get(int hash) {

    }
    V& operator[](int hash) {

    }
    bool contains(int hash) {
        get(hash) == EmptyVal;
    }
    // allocator_->allocate(size);
    
};

/**
 * White upper, black lower.
 * Ex. "Brnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR"
 */
string boardToStr(vector<vector<chess*>> const & board, bool turn){
    string res = "";
    if (turn == PLAYER_BLACK){
        res += "B";
    } else {
        res += "W";
    }
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            switch (board[i][j]->c_type)
            {
            case KING:
                if (board[i][j]->player == PLAYER_WHITE){
                    res += "K";
                } else {
                    res += "k";
                }
                break;
            case KNIGHT:
                if (board[i][j]->player == PLAYER_WHITE){
                    res += "N";
                } else {
                    res += "n";
                }
                break;
            case QUEEN:
                if (board[i][j]->player == PLAYER_WHITE){
                    res += "Q";
                } else {
                    res += "q";
                }
                break;
            case ROOK:
                if (board[i][j]->player == PLAYER_WHITE){
                    res += "R";
                } else {
                    res += "r";
                }
                break;
            case BISHOP:
                if (board[i][j]->player == PLAYER_WHITE){
                    res += "B";
                } else {
                    res += "b";
                }
                break;
            case PAWN:
                if (board[i][j]->player == PLAYER_WHITE){
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
// HashTable<int64_t, uint16_t, 0, normal_collision_handler> table(nullptr, nullptr);

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

#endif
