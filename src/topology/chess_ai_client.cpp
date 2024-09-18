#include <cstdint>
#include <rpc/client.h>
#include <stddef.h>
#include <iostream>
#include "../chess/chess.hpp"
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
    rpc::client client("127.0.0.1", 8080);

    std::string from, to;
    while(true) {
        std::cout << "Enter your move (e.g., e2 e4): ";
        std::cin >> from >> to;

        if (from == "exit" || to == "exit") break;

        chess_move move(point(from[0] - 'a', 8 - (from[1] - '0')), point(to[0] - 'a', 8 - (to[1] - '0')));
        int16_t encoded_move = combine_c_move(move);
    }

    return 0;
}
