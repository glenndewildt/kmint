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
public:
void OnExit(){
    std::cout<< "Exit  go_to_bandlit state"<<std::endl;


};
void OnEnter(){
    std::cout<< "Enter  go_to_bandlit state"<<std::endl;

};
    go_to_bandlit(state_object* object):counter{0}, object{object}{};


void check_state(std::vector< board_piece*> &_board_pieces, point my_location) {



};

void update() {
    std::cout << "go_to_bandlit state" << std::endl;
};

void draw() {};

};
}


#endif //KMINTFRAMEWORK_GO_TO_BANDLIT_H
