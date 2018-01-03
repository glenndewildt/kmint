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
#include <Movable_objects/Cow/Cow.h>

namespace kmint {

    class Bunny : public free_roaming_board_piece {
        image_drawable _drawable;

    public:
        Bunny(point location, const image &i) : free_roaming_board_piece { location }, _drawable { *this,i } {};
        const drawable &get_drawable() const override { return _drawable; }

        void update(float dt, std::vector< board_piece*> _board_pieces) {
            auto curLoc = location();
            auto vec = Linal::G2D::Vector(curLoc.x(), curLoc.y());

            for (auto bp : _board_pieces)
            {
                if (dynamic_cast<kmint::Cow*>(bp))
                {
                    auto targetLoc = bp->location();
                    auto targetVec = Linal::G2D::Vector(targetLoc.x(), targetLoc.y());

                    vec = (targetVec - vec).GetUnitVector();
                }
            }

            set_point(kmint::point { vec.x() + curLoc.x(), vec.y() + curLoc.y() });
        }
    };
}


#endif //KMINTFRAMEWORK_BUNNY_H
