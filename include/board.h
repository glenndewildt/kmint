#ifndef _KMINT_BOARD_H
#define _KMINT_BOARD_H

#include "window.h"
#include "renderer.h"
#include "image.h"
#include <vector>

namespace kmint {
    class board_piece;
    class board {
        window _window;
        renderer _renderer;
        std::vector< board_piece*> _board_pieces;
    public:
        board();
        void play();
        void add_board_piece( board_piece& a) {
            _board_pieces.push_back(&a);
        }
    };
}
#endif
