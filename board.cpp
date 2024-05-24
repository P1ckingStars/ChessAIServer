#include "board.hpp"
#include <iostream>

using namespace std;

#define CAPITAL ('A' - 'a')

/*
    KING    = 0, 
    QUEEN   = 1, 
    ROOK    = 2, 
    BISHOP  = 3, 
    KNIGHT  = 4, 
    PAWN    = 5,
*/

char chess_char[6] = {
    'n',
    'q',
    'r',
    'b',
    'k',
    'p'
};
  
board::board() {
    player_turns = PLAYER_WHITE;
    grid = vector<vector<chess *>>(8, vector<chess *>(8, nullptr));
    grid[0][0]  = new chess { point {0, 0}, PLAYER_WHITE, ROOK      };
    grid[0][1]  = new chess { point {0, 1}, PLAYER_WHITE, KNIGHT    };
    grid[0][2]  = new chess { point {0, 2}, PLAYER_WHITE, BISHOP    };
    grid[0][3]  = new chess { point {0, 3}, PLAYER_WHITE, KING      };
    grid[0][4]  = new chess { point {0, 4}, PLAYER_WHITE, QUEEN     };
    grid[0][5]  = new chess { point {0, 5}, PLAYER_WHITE, BISHOP    };
    grid[0][6]  = new chess { point {0, 6}, PLAYER_WHITE, KNIGHT    };
    grid[0][7]  = new chess { point {0, 7}, PLAYER_WHITE, ROOK      };
                                         
    grid[7][0]  = new chess { point {7, 0}, PLAYER_BLACK, ROOK      };
    grid[7][1]  = new chess { point {7, 1}, PLAYER_BLACK, KNIGHT    };
    grid[7][2]  = new chess { point {7, 2}, PLAYER_BLACK, BISHOP    };
    grid[7][3]  = new chess { point {7, 3}, PLAYER_BLACK, KING      };
    grid[7][4]  = new chess { point {7, 4}, PLAYER_BLACK, QUEEN     };
    grid[7][5]  = new chess { point {7, 5}, PLAYER_BLACK, BISHOP    };
    grid[7][6]  = new chess { point {7, 6}, PLAYER_BLACK, KNIGHT    };
    grid[7][7]  = new chess { point {7, 7}, PLAYER_BLACK, ROOK      };

    for (uint8_t i = 0; i < 8; i++) {
        grid[1][i]  = new chess { point {1, i}, PLAYER_WHITE, PAWN };
        grid[6][i]  = new chess { point {6, i}, PLAYER_BLACK, PAWN };
    }
}

void board::print_board() {
    cout << "    ";
    for (int i = 0; i < 8; i++) {
        cout << i << "   ";
    }
    cout << endl;
    for (int x = 0; x < 8; x++) {
        cout << x << "   ";
        for (int y = 0; y < 8; y++) {
            auto c = this->grid[x][y];
            if (c) cout << (char)(chess_char[c->c_type] + (CAPITAL * c->player)) << "   ";
            else cout << "    ";
        } 
        cout << endl;
    }
    cout << endl;
}

bool board::next_move(chess_move c_move) {
    if (c_move.from.x < 0 || c_move.from.x >= 8 || c_move.from.y < 0 || c_move.from.y >= 8) return false;
    cout << "in board" << endl;
    if (grid[c_move.from.x][c_move.from.y] == nullptr && grid[c_move.from.x][c_move.from.y]->player == player_turns) return false;
    cout << "is your chess" << endl;
    if (grid[c_move.from.x][c_move.from.y]->legal_move(this->grid).count(c_move.to)) {
        grid[c_move.to.x][c_move.to.y]      = grid[c_move.from.x][c_move.from.y];
        grid[c_move.to.x][c_move.to.y]->pos = c_move.to;
        grid[c_move.from.x][c_move.from.y]  = nullptr;
        if ((c_move.to.x == 0 || c_move.to.x == 7) && grid[c_move.to.x][c_move.to.y]->c_type == PAWN) {
            grid[c_move.to.x][c_move.to.y]->c_type = QUEEN;
        } 
        player_turns = !player_turns;
        cout << "player_turns " << player_turns << endl;
        return true;
    }
    return false;
}
bool board::turns() {
    return player_turns;
}
bool board::end() {
    bool white_king_alive = 0;
    bool black_king_alive = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (grid[x][y] && grid[x][y]->c_type == KING) {
                grid[x][y]->player == PLAYER_WHITE ? (white_king_alive = 1) : (black_king_alive = 1);
            }
        }
    }
    return !white_king_alive || !black_king_alive;

}