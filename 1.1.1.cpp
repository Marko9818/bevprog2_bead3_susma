#include "amoebawidget.hpp"

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
                gout << move_to(x + cellSize / 3, y + cellSize / 4) << text("O");
            }
        }
    }
    gout << refresh;
}
void AmoebaWidget::handle(genv::event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        // Calculate cell coordinates based on mouse position
        int cellX = (ev.pos_x - _pos_x) / (cellSize + cellPadding);
        int cellY = (ev.pos_y - _pos_y) / (cellSize + cellPadding);
        // Place player's mark on the board
        if (cellX >= 0 && cellX < boardSize && cellY >= 0 && cellY < boardSize && board[cellY][cellX] == '.') {
            board[cellY][cellX] = (currentPlayer == 0) ? 'X' : 'O';
            currentPlayer = (currentPlayer + 1) % 2;
            draw();
        }
    }
}
