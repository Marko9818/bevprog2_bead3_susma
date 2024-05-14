#include "amoebawidget.hpp"
#include <iostream>
using namespace genv;


AmoebaWidget::AmoebaWidget(Window* window, int pos_x, int pos_y, int width, int height)
    : OSWidget(window, pos_x, pos_y, width, height) {
    cellSize = (width - 20) / boardSize;
    cellPadding = 2;
    currentPlayer = 0;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            board[i][j] = '.';
        }
    }
}

void AmoebaWidget::draw() const {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            int x = _pos_x + j * (cellSize + cellPadding);
            int y = _pos_y + i * (cellSize + cellPadding);
            gout << move_to(x, y) << color(200, 200, 200) << box(cellSize, cellSize);
            if (board[i][j] == 'X') {
                gout << color(255, 0, 0);
                gout << move_to(x + cellSize / 4, y + cellSize / 4) << line(cellSize / 2, cellSize / 2);
                gout << move_to(x + cellSize / 4, y + cellSize * 3 / 4) << line(cellSize / 2, -cellSize / 2);
            } else if (board[i][j] == 'O') {
                gout << color(0, 0, 255);
                gout << move_to(x + cellSize /3, y + cellSize / 4) << text("O");
            }
        }
    }
    gout << refresh;
}

void AmoebaWidget::handle(genv::event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        int cellX = (ev.pos_x - _pos_x) / (cellSize + cellPadding);
        int cellY = (ev.pos_y - _pos_y) / (cellSize + cellPadding);
        if (cellX >= 0 && cellX < boardSize && cellY >= 0 && cellY < boardSize && board[cellY][cellX] == '.') {
            board[cellY][cellX] = (currentPlayer == 0) ? 'X' : 'O';
            currentPlayer = (currentPlayer + 1) % 2;
            draw();
            if (checkWin()) {
                std::cout << "Player " << ((currentPlayer == 0) ? "Player1" : "Player2") << " wins!" << std::endl;
            }
        }
    }
}

bool AmoebaWidget::checkWin() const {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize - 4; ++j) {
            if (board[i][j] != '.' && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] &&
                board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4]) {
                return true;
            }
            if (board[j][i] != '.' && board[j][i] == board[j + 1][i] && board[j][i] == board[j + 2][i] &&
                board[j][i] == board[j + 3][i] && board[j][i] == board[j + 4][i]) {
                return true;
            }
        }
    }
    for (int i = 0; i < boardSize - 4; ++i) {
        for (int j = 0; j < boardSize - 4; ++j) {
            if (board[i][j] != '.' && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] &&
                board[i][j] == board[i + 3][j + 3] && board[i][j] == board[i + 4][j + 4]) {
                return true;
            }
            if (board[i][j + 4] != '.' && board[i][j + 4] == board[i + 1][j + 3] && board[i][j + 4] == board[i + 2][j + 2] &&
                board[i][j + 4] == board[i + 3][j + 1] && board[i][j + 4] == board[i + 4][j]) {
                return true;
            }
        }
    }
    return false;
}
