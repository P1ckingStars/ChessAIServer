#include "player.hpp"
#include <iostream>

using namespace std;

player::player(bool side) {
    this->side = side;
}

chess_move terminal_player::make_move(vector<vector<chess *>> const & state) {
    if (this->side == PLAYER_WHITE) {
        cout << "WHITE turn: " << endl;
    } else {
        cout << "BLACK turn: " << endl;
    }
    int from_x;
    int from_y;
    int to_x;
    int to_y;
    cin >> from_x;
    cin >> from_y;
    cin >> to_x;
    cin >> to_y;

    return chess_move {
        point {
            (int8_t)from_x,
            (int8_t)from_y,
        },
        point {
            (int8_t)to_x,
            (int8_t)to_y
        }
    };
}
