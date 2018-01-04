//
// Created by administrator on 4-1-18.
//

#ifndef KMINTFRAMEWORK_WANDERING_STATE_H
#define KMINTFRAMEWORK_WANDERING_STATE_H


#include <iostream>
#include "base_state.h"

class wandering_state: public base_state {
     void check_state() {
         //check condition of state
     };

     void update() {
         std::cout<< "wandering state"<<std::endl;
     };

     void draw() {};

};


#endif //KMINTFRAMEWORK_WANDERING_STATE_H
