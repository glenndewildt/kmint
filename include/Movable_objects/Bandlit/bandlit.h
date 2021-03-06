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
        enum Name { AXEL, ANDRE, FRANS, JOHNNIE };

        Name name;
        int money;
        double pause;
        double time;
        double wait;
        int des_node_id;


        bandlit(const graph &graph, node_id nid, const image &i, city* city, Name name ):name{name},stad{city},pause{0},time{0}, wait{0},money{1000},state_object(graph,nid,i){
        };

        virtual void update(float dt, std::vector< board_piece*> &_board_pieces)override {
            float difference = dt - time;

            if(difference > 0.2){
                state_object::update( _board_pieces);

                time = dt;

            }else{
            }


        }



    };

}

#endif //KMINTFRAMEWORK_BANDLIT_H
