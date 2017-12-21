//
// Created by administrator on 21-12-17.
//

#ifndef KMINTFRAMEWORK_BUNNY_H
#define KMINTFRAMEWORK_BUNNY_H
#include <free_roaming_board_piece.h>

namespace kmint {

    class Bunny : public free_roaming_board_piece {
    public:
        Bunny(point _point) : free_roaming_board_piece(_point) {};


        const drawable &get_drawable() const;
    };
}


#endif //KMINTFRAMEWORK_BUNNY_H
