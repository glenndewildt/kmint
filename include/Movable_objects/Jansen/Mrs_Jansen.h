//
// Created by administrator on 6-1-18.
//

#ifndef KMINTFRAMEWORK_MRS_JANSEN_H
#define KMINTFRAMEWORK_MRS_JANSEN_H


#include <Movable_objects/State/state_object.h>

namespace kmint {
    class Mrs_Jansen: public state_object {
    private:

    public:
        int pause;
        int time;
        int wait;


        Mrs_Jansen(const graph &graph, node_id nid, const image &i):pause{0},time{0}, wait{0},state_object(graph,nid,i){
        };
        virtual void update(float dt, std::vector< board_piece*> &_board_pieces)override
        {

            int difference = dt - pause;

                pause += difference;


            time += difference;


            if(time > 0){
                if(wait > 1){
                    time = 0;
                    wait = 0;

                }
                wait += difference;

            }else{
                set_node_id({get_node_id()+1});
            }
           pause+= difference;
        }


    };
}

#endif //KMINTFRAMEWORK_MRS_JANSEN_H
