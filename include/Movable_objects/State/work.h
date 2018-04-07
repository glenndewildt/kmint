//
// Created by administrator on 7-4-18.
//

#ifndef KMINTFRAMEWORK_WORK_H
#define KMINTFRAMEWORK_WORK_H

#include <Movable_objects/Bandlit/bandlit.h>
#include <Movable_objects/Manager/Manager.h>
#include "base_state.h"
#include "state_object.h"

namespace kmint{
    class work:   public base_state {
    private:
        int counter;
        state_object* object;
    public:
        void OnExit(){
            std::cout<< "Exit  work state"<<std::endl;


        };
        void OnEnter(){
            std::cout<< "Enter  work state"<<std::endl;

        };
        work(state_object* object):counter{0}, object{object}{};


        void check_state(std::vector< board_piece*> &_board_pieces, point my_location) {
            if (dynamic_cast<kmint::bandlit *>(object)) {

                kmint::bandlit *band = dynamic_cast<kmint::bandlit *>(object);
               if(band->des_node_id != -1){

                   if(counter > 2) {
                       counter = 0;
                       band->des_node_id = -1;
                   }
                   counter++;
               }else{

                       band->set_state("wandering");

               }
            }

        }




    void update() {
        std::cout<< "Work";
        if (dynamic_cast<kmint::bandlit *>(object)) {

            kmint::bandlit *band = dynamic_cast<kmint::bandlit *>(object);
            if(band->des_node_id != -1){
                band->set_node_id(band->des_node_id);

            }
        }



    };

    void draw() {};

};
}
#endif //KMINTFRAMEWORK_WORK_H
