#include "amoebawidget.hpp"

AmoebaWidget::AmoebaWidget(Window* window, int pos_x, int pos_y, int width, int height)
    : OSWidget(window, pos_x, pos_y, width, height) {
    cellSize = (width - 20) / boardSize;
    cellPadding = 2;
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
            gout << move_to(x, y) << color(255, 255, 255) << box(cellSize, cellSize);
        }
    }
    gout << refresh;
}

void AmoebaWidget::handle(genv::event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        int cellX = (ev.pos_x - _pos_x) / (cellSize + cellPadding);
        int cellY = (ev.pos_y - _pos_y) / (cellSize + cellPadding);
        if (cellX >= 0 && cellX < boardSize && cellY >= 0 && cellY < boardSize && board[cellY][cellX] == '.') {
            board[cellY][cellX] = 'X';
            draw();
        }
    }
}
