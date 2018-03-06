//
// Created by administrator on 6-1-18.
//

#ifndef KMINTFRAMEWORK_SHEEP_H
#define KMINTFRAMEWORK_SHEEP_H

#include <Movable_objects/State/state_object.h>

namespace kmint {
    class Sheep: public state_object {
    private:

    public:
        int thurst;
        int miss;
        int mrs;

        Sheep(const graph &graph, node_id nid, const image &i):thurst{0},miss{50},mrs{50},state_object(graph,nid,i){
        };
        virtual void update(float dt, std::vector< board_piece*> &_board_pieces)override
        {
            int difference = dt - thurst;

            if(thurst = 100){
                set_state("retieve");

            }else{
                thurst += difference;
            }
            state_object::update( _board_pieces);
        }


    };
}


#endif //KMINTFRAMEWORK_SHEEP_H
