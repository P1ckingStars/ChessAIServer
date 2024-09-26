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
        return res;
    }
};


int main() {
    game b = game(new terminal_player(0), new remote_player(1, "127.0.0.1", 8080));   
    b.run();
    return 0;
}
