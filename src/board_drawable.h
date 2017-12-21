//
// Created by administrator on 18-12-17.
//

#ifndef KMINTFRAMEWORK_BOARD_DRAWABLE_H
#define KMINTFRAMEWORK_BOARD_DRAWABLE_H


#include <image.h>
#include <drawable.h>
#include <free_roaming_board_piece.h>

namespace kmint {
    class renderer;
    class board_drawable : public free_roaming_board_piece {
    public:
        board_drawable();
        void draw(const renderer &r) const ;
    };
}



#endif //KMINTFRAMEWORK_BOARD_DRAWABLE_H
