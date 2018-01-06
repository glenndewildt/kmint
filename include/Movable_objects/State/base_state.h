//
// Created by administrator on 4-1-18.
//

#ifndef KMINTFRAMEWORK_BASE_STATE_H
#define KMINTFRAMEWORK_BASE_STATE_H
#include <vector>
#include "board_piece.h"


namespace kmint {


    class base_state {
    private:
    public:
        virtual ~base_state() {};

        virtual void check_state(std::vector< board_piece*> &_board_pieces, point my_location) {};

        virtual void update() {};

        virtual void draw() {};
    };
}
#endif //KMINTFRAMEWORK_BASE_STATE_H
