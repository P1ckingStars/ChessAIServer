
#include "game.hpp"

game::game() {
    p_white = new terminal_player(PLAYER_WHITE);
    p_black = new terminal_player(PLAYER_BLACK);
    m_board = board();
}

void game::run() {
    while (!m_board.end()) {
        m_board.print_board();
        if (m_board.turns() == PLAYER_BLACK) {
            while (!m_board.next_move(p_black->make_move(m_board.grid)));
        } else {
            while (!m_board.next_move(p_white->make_move(m_board.grid)));
        }
    }

}