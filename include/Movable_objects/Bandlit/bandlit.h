//
// Created by administrator on 6-3-18.
//

#ifndef KMINTFRAMEWORK_BANDLIT_H
#define KMINTFRAMEWORK_BANDLIT_H

#include <Movable_objects/State/state_object.h>
#include <city.h>

namespace kmint {
    class bandlit: public state_object {
    private:
        city* stad;

    public:
        int money;
        int pause;
        int time;
        int wait;


        bandlit(const graph &graph, node_id nid, const image &i, city* city):stad{city},pause{0},time{0}, wait{0},money{1000},state_object(graph,nid,i){
        };

        virtual void update(float dt, std::vector< board_piece*> &_board_pieces)override {
//            for(auto& locations : stad->_nodes){
//                if((locations.location().x() -20 < this->location().x())&& (locations.location().x() +20 > this->location().x()) && (locations.location().x() -20 < this->location().y())&& (locations.location().y() +20 > this->location().y())){
//                std::cout<<"close by block";
//                }
//            }
            state_object::update( _board_pieces);
        }



    };

}

#endif //KMINTFRAMEWORK_BANDLIT_H
