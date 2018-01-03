#ifndef _KMINT_FREE_ROAMING_ACTOR_H
#define _KMINT_FREE_ROAMING_ACTOR_H

#include "board_piece.h"
#include "point.h"

namespace kmint {
    class free_roaming_board_piece : public board_piece {
        point _location;
    public:
        free_roaming_board_piece(point location) : board_piece {}, _location {location} {}
        void set_point(point pos){ _location = pos;}
        point location() const override { return _location; }
    };
}

#endif
