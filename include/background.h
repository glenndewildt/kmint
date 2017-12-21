#ifndef _KMINT_BACKGROUND_H
#define _KMINT_BACKGROUND_H

#include "point.h"
#include "free_roaming_board_piece.h"
#include "image_drawable.h"

namespace kmint {
    class image;
    class background : public free_roaming_board_piece {
        image_drawable _drawable;
    public:
        background(const image &i) : free_roaming_board_piece { {640.0, 360.0} }, _drawable {*this, i} {}
        const drawable& get_drawable() const override { return _drawable; };
    };
}

#endif
