//
// Created by administrator on 4-1-18.
//

#ifndef KMINTFRAMEWORK_WANDERING_STATE_H
#define KMINTFRAMEWORK_WANDERING_STATE_H


#include <iostream>
#include <Movable_objects/Bunny/Bunny.h>
#include "base_state.h"
#include "state_object.h"

namespace kmint {

    class wandering_state : public base_state {
    private:

        state_object* object;
    public:
        wandering_state(state_object* object): object{object}{};
        void check_state(std::vector< board_piece*> _board_pieces, point my_location) {
            //check condition if near by bunny
            for (auto bp : _board_pieces) {
                if (dynamic_cast<kmint::Bunny *>(bp)) {
                    auto loc = bp->location();

                    auto diff = (my_location - loc);
                    if( std::abs(diff.x()) + std::abs(diff.y()) < 50){
                        std::cout<< "Near by bunny";
                        object->set_state("sleep");
                    }

                }
            }

        };

        void update() {
            std::cout << "wandering state" << std::endl;

            if(object->get_node_id() < 1000){
                object->set_node_id({object->get_node_id()+1});
            }
        };

        void draw() {};

    };
}


#endif //KMINTFRAMEWORK_WANDERING_STATE_H
