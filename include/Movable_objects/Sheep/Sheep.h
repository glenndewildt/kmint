//
// Created by administrator on 4-1-18.
//

#ifndef KMINTFRAMEWORK_SHEEP_H
#define KMINTFRAMEWORK_SHEEP_H


#include <array>
#include <map>
#include "base_state.h"
#include <graph_bound_board_piece.h>
#include <iostream>

namespace kmint {

    class Sheep : public graph_bound_board_piece{
    protected:
        base_state *current_state;
        std::map<std::string, base_state *> states;
    public:
        Sheep(const graph &graph, node_id nid, const image &i):graph_bound_board_piece(graph, nid, i){

        };

        void update(float dt, std::vector< board_piece*> _board_pieces)
        {
            std::cout << "update sheep" <<std::endl;
            if(get_node_id() < 1000){
                set_node_id({get_node_id()+1});
            }
            update();
        }
         void update() {
            current_state->check_state();
            current_state->update();
        };

        virtual void add_state(base_state* enemy_state, const char* key) {

            states.insert(std::make_pair(std::string(key), enemy_state));
        };
        virtual void set_state(const char* key){
            current_state = states[std::string(key)];
        };


    };
}


#endif //KMINTFRAMEWORK_SHEEP_H
