//
// Created by administrator on 5-1-18.
//

#ifndef KMINTFRAMEWORK_SLEEP_STATE_H
#define KMINTFRAMEWORK_SLEEP_STATE_H


#include <iostream>
#include <board_piece.h>
#include <bunny.h>
#include "base_state.h"
#include "state_object.h"

namespace kmint {

    class sleep_state : public base_state {
    private:

        state_object* object;
    public:
        sleep_state(state_object* object): object{object}{};
        void check_state(std::vector< board_piece*> &_board_pieces, point my_location) {
            int count = 0;
            int counter = 0 ;

            //check condition if near by bunny
            for (auto bp : _board_pieces) {
                if (dynamic_cast<Bunny *>(bp)) {

                    auto loc = bp->location();

                    auto diff = (my_location - loc);

                    if( std::abs(diff.x()) + std::abs(diff.y()) < 15){
                        std::cout<< "eatt";
                        _board_pieces.erase(_board_pieces.begin()+counter);
                    }
                    if( std::abs(diff.x()) + std::abs(diff.y()) < 50){

                        count++;
                    }

                }
                counter ++;

            }
            if(count < 1){
                std::cout<< " nearby bunny";

                object->set_state("wandering");
            }
        };

        void update() {
            std::cout << "sleep state" << std::endl;
        };

        void draw() {};
        void OnExit(){
            std::cout<< "Exit  sleep state"<<std::endl;


        };
        void OnEnter(){
            std::cout<< "Enter  sleep state"<<std::endl;
        };

    };

}





#endif //KMINTFRAMEWORK_SLEEP_STATE_H
