//
// Created by administrator on 21-12-17.
//

#ifndef KMINTFRAMEWORK_BUNNY_H
#define KMINTFRAMEWORK_BUNNY_H
#include <free_roaming_board_piece.h>
#include "graph_drawable.h"
#include <node.h>
#include <image_drawable.h>
#include <linal/vector.h>

namespace kmint {

    class Bunny : public free_roaming_board_piece {
        image_drawable _drawable;

    public:
        Bunny(point location, const image &i) : free_roaming_board_piece { location }, _drawable { *this,i } {};
        const drawable &get_drawable() const override { return _drawable; }

        void update(float dt) {
            auto curLoc = location();
            auto vec = Linal::G2D::Vector(curLoc.x() + (1), curLoc.y() - (1));
            set_point(kmint::point { vec.x(), vec.y() });
        }
    };
}


#endif //KMINTFRAMEWORK_BUNNY_H
