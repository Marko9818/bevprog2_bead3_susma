#ifndef AMOEBA_WIDGET_HPP
#define AMOEBA_WIDGET_HPP

#include "oswidget.hpp"
#include "graphics.hpp"

class AmoebaWidget : public OSWidget {
private:
    static const int boardSize = 15;
    char board[boardSize][boardSize];
    int cellSize;
    int cellPadding;

public:
    AmoebaWidget(Window* window, int pos_x, int pos_y, int width, int height);
    virtual void draw() const override;
    virtual void handle(genv::event ev) override;
};

#endif // AMOEBA_WIDGET_HPP
