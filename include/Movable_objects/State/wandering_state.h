//
// Created by administrator on 4-1-18.
//

#ifndef KMINTFRAMEWORK_WANDERING_STATE_H
#define KMINTFRAMEWORK_WANDERING_STATE_H


#include <iostream>
#include <Movable_objects/Fan/Fan.h>
#include <Movable_objects/Bandlit/bandlit.h>
#include <Movable_objects/Manager/Manager.h>
#include "base_state.h"
#include "state_object.h"

namespace kmint {

    class wandering_state : public base_state {
    private:

        state_object* object;
         int next_node_id;
        int weight;
    public:

        wandering_state(state_object* object): object{object}, next_node_id{-1}{};
        void check_state(std::vector< board_piece*> &_board_pieces, point my_location) {
            //check condition if near by bunny
            if (dynamic_cast<kmint::bandlit *>(object)) {

                kmint::bandlit* band =dynamic_cast<kmint::bandlit *>(object);
                if( band->money <= 900){
                    std::cout<< "Geen money om te lopen";
                    for (auto bp : _board_pieces) {
                        if (dynamic_cast<Manager *>(bp)) {

                            kmint::Manager* man =dynamic_cast<kmint::Manager *>(bp);
                            if(!man->is_busy){
                                // call manager
                                man->call_manager(1);
                                // set state to wait for manager
                                object->set_state("wait");
                                std::cout<< "wait for manager ";


                            }else{
                                std::cout<< "Manager is busy";

                            }

                        }

                    }                  //  object->set_state("sleep");
                }else{
                    if(band->money >= 0){
                        band->money = band->money - 20;
                        std::cout<< "money - 20 G";
                    }


                }

            }


        };

        void update() {
            std::cout << "wandering state id = "<< object->get_node_id() << std::endl;
            std::unordered_map< int,int> node_ids;
            if(next_node_id != -1){
                if(weight >0){
                    std::cout<<"Weight : "<< weight;
                    weight--;

                } else{
                    object->set_node_id(next_node_id);
                    next_node_id = -1;
                }


            } else{
                for(auto& node : object->get_graph()){
                    if(node.id() == object->get_node_id()){
                        for(auto& edge : node){
                            for(auto& edge_node :edge.to()){

                                if(edge_node.to().id() != object->get_node_id()){
                                    node_ids.insert(std::pair<int, int>(edge_node.to().id(), edge.weight()));
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
                for(auto& index : node_ids){
                    if(number_index == number){
                        next_node_id = index.first;
                        weight = index.second;
                    }
                    number_index++;
                }
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
