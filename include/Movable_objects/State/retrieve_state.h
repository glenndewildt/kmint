//
// Created by administrator on 6-1-18.
//

#ifndef KMINTFRAMEWORK_RETRIEVE_STATE_H
#define KMINTFRAMEWORK_RETRIEVE_STATE_H

#include <iostream>
#include <board_piece.h>
#include <bunny.h>
#include <Movable_objects/Sheep/Sheep.h>
#include <random>
#include "base_state.h"
#include "state_object.h"

namespace kmint {

    class retrieve_state : public base_state {
    private:

        state_object* object;
    public:
        retrieve_state(state_object* object): object{object}{};
        void chose_person(Sheep* sheep){
            int randNum = rand()%(100-0 + 1) + 0;
            if(randNum > sheep->miss  ){
                std::cout <<  sheep->miss<< std::endl;

                int add = rand()%(100-0 + 1) + 0;
                if(add > 50){
                    if(sheep->miss <=95){
                        sheep->miss += 5;
                        sheep->mrs -=5;
                    }
                }


            }else{
                int add = rand()%(100-0 + 1) + 0;

                if(add > 50){
                    if(sheep->mrs <=95){
                        sheep->mrs += 5;
                        sheep->miss -=5;
                    }
                }

            }


        };

        void check_state(std::vector< board_piece*> &_board_pieces, point my_location) {


            if (dynamic_cast<Sheep*>(object)) {
                Sheep* dog = dynamic_cast<Sheep*>(object);
                if(dog->thurst > 0 ){
                    chose_person(dog);
                    //object->set_state("wandering");
                }

            }

        };

        void update() {
            std::cout << "retieve state" << std::endl;
        };

        void draw() {};

    };
}





#endif //KMINTFRAMEWORK_RETRIEVE_STATE_H
