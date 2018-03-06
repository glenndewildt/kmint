//
// Created by administrator on 4-1-18.
//

#ifndef KMINTFRAMEWORK_WANDERING_STATE_H
#define KMINTFRAMEWORK_WANDERING_STATE_H


#include <iostream>
#include <Movable_objects/Bunny/Bunny.h>
#include <Movable_objects/Bandlit/bandlit.h>
#include "base_state.h"
#include "state_object.h"

namespace kmint {

    class wandering_state : public base_state {
    private:

        state_object* object;
    public:

        wandering_state(state_object* object): object{object}{};
        void check_state(std::vector< board_piece*> &_board_pieces, point my_location) {
            //check condition if near by bunny
            if (dynamic_cast<kmint::bandlit *>(object)) {

                kmint::bandlit* band =dynamic_cast<kmint::bandlit *>(object);
                if( band->money <=100){
                    std::cout<< "Geen money om te lopen";
                    object->set_state("sleep");
                }else{
                    band->money = band->money - 20;
                    std::cout<< "money - 20 G";

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
        void OnExit(){
            std::cout<< "Exit  wandering state"<<std::endl;


        };
        void OnEnter(){
            std::cout<< "Enter  wandering state"<<std::endl;
        };

    };
}


#endif //KMINTFRAMEWORK_WANDERING_STATE_H
