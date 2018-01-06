//
// Created by administrator on 6-1-18.
//

#ifndef KMINTFRAMEWORK_ISONWATER_H
#define KMINTFRAMEWORK_ISONWATER_H

#include <Movable_objects/Bunny/Bunny.h>
#include "board_piece.h"

class IsOnWater {
    std::vector<kmint::board_piece*> _boardPieces;

public:
    IsOnWater(std::vector<kmint::board_piece*> _boardPieces) : _boardPieces(_boardPieces) {}

    bool operator()(kmint::board_piece* target) {
        if (dynamic_cast<kmint::Bunny*>(target))
        {
            auto bunny = dynamic_cast<kmint::Bunny*>(target);
            if (bunny->isOnWater(_boardPieces))
            {
                return true;
            }
        }
        return false;
    }

};

#endif //KMINTFRAMEWORK_ISONWATER_H
