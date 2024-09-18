#include <cstdint>
#include <rpc/client.h>
#include <stddef.h>
#include <iostream>
#include "../chess/chess.hpp"
#include "../chess/game.hpp"
#include "../chess/player.hpp"
#include "../hashtable/hashable.hpp"
#include "bss.h"


class remote_player: public player {
    rpc::client * client;
public:
    remote_player(bool side, std::string const & addr, int16_t port) : player(side) {
        client = new rpc::client(addr, port);
    }
    chess_move make_move(vector<vector<chess *> > const & state) {
        chess_move res;
        try {
            res = client->call(RPC_SUBMIT_TASK, compressBoard(state, this->side)).as<chess_move>();
        } catch (const std::exception &e) {
            std::cerr << "Balancer failed: " << e.what() << std::endl;
        }
    }
};

int16_t combine_c_move(const chess_move &move) {
    int16_t result = 0;
    result |= (move.from.x & 0x0F) << 12;
    result |= (move.from.y & 0x0F) << 8;
    result |= (move.to.x & 0x0F) << 4;
    result |= (move.to.y & 0x0F);
    return result;
}

int main() {
    game b = game();   
    b.run();
    return 0;
}
