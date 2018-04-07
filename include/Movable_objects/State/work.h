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

                kmint::bandlit* band =dynamic_cast<kmint::bandlit *>(object);
                for (auto bp : _board_pieces) {
                    if (dynamic_cast<Manager *>(bp)) {

                        kmint::Manager* man =dynamic_cast<kmint::Manager *>(bp);
                        if(man->get_node_id() == object->get_node_id()){
                            std::cout<< "manager is near appointment";

                        }

                    }

                }
            }

        }


    };

    void update() {
        std::cout << "wait state" << std::endl;
    };

    void draw() {};

};
}
#endif //KMINTFRAMEWORK_WORK_H
