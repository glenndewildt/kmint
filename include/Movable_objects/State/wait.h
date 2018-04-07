//
// Created by administrator on 7-4-18.
//

#include <Movable_objects/Bandlit/bandlit.h>
#include <Movable_objects/Manager/Manager.h>
#include "base_state.h"
#include "state_object.h"

#ifndef KMINTFRAMEWORK_WAIT_H
#define KMINTFRAMEWORK_WAIT_H

#endif //KMINTFRAMEWORK_WAIT_H
namespace kmint{
class wait:   public base_state {
private:
    int counter;
    state_object* object;
public:
    void OnExit(){
        std::cout<< "Exit  wait state"<<std::endl;


    };
    void OnEnter(){
        std::cout<< "Enter  wait state"<<std::endl;

    };
    wait(state_object* object):counter{0}, object{object}{};


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