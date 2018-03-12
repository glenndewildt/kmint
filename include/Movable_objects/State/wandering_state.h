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
                  //  object->set_state("sleep");
                }else{
                    band->money = band->money - 20;
                    std::cout<< "money - 20 G";

                }

            }


        };

        void update() {
            std::cout << "wandering state id = "<< object->get_node_id() << std::endl;
            std::vector<int> node_ids;

            for(auto& node : object->get_graph()){
                if(node.id() == object->get_node_id()){
                    for(auto& edge : node){
                        for(auto& edge_node :edge.to()){
                            std::cout << "edge id = "<< edge_node.to().id()<< std::endl;

                            if(edge_node.to().id() != object->get_node_id()){
                                node_ids.push_back(edge_node.to().id());
                            }

                        }


                    }
                }
            }

            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(0,node_ids.size());
            int number = dist6(rng);
            int number_index = 0;
            for(int index : node_ids){
                if(number_index == number){
                     object->set_node_id(index);

                }
                number_index++;
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
