//
// Created by administrator on 6-4-18.
//

#ifndef KMINTFRAMEWORK_GO_TO_BANDLIT_H
#define KMINTFRAMEWORK_GO_TO_BANDLIT_H

#include "base_state.h"
#include "state_object.h"

namespace kmint {

class go_to_bandlit:  public base_state {
private:
int counter;
state_object* object;
    std::vector<node> path;
public:
void OnExit(){
    std::cout<< "Exit  go_to_bandlit state"<<std::endl;


};
void OnEnter(){
    std::cout<< "Enter  go_to_bandlit state"<<std::endl;

};
    go_to_bandlit(state_object* object):counter{0}, object{object}{};


void check_state(std::vector< board_piece*> &_board_pieces, point my_location) {

    if (dynamic_cast<kmint::Manager *>(object)) {

        kmint::Manager* man =dynamic_cast<kmint::Manager *>(object);

                if(man->get_node_id() == man->dest_node_id){
                    std::cout<< "manager is with bandlit"<< std::endl;
                    man->is_busy = false;
                    man->set_state("wandering");
                }



        }


};

void update() {
    // astar search algoritme
    if (dynamic_cast<kmint::Manager *>(object)) {

        kmint::Manager* man =dynamic_cast<kmint::Manager *>(object);

        man->set_node_id(man->dest_node_id);



    }};

void draw() {

};

};
}


#endif //KMINTFRAMEWORK_GO_TO_BANDLIT_H
