#include <rpc/client.h>
#include <stddef.h>
#include <iostream>
#include "../chess/chess.hpp"

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

    std::from, to;
    while(true) {
        std::cout << "Enter your move (e.g., e2 e4): ";
        std::cin >> from >> to;

        if (from == "exit" || to == "exit") break;

        chess_move move(from[0] - 'a', 8 - (from[1] - '0'), to[0] - 'a', 8 - (to[1] - '0'));
        int16_t encoded_move = combine_c_move(move);

        try {
            client.call("submit_task", encoded_move);
        } catch (const std::exception &e) {
            std::cerr << "Balancer failed: " << e.what() << std::endl;
        }
    }

    return 0;
}
