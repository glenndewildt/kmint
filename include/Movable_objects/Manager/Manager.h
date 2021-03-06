//
// Created by administrator on 6-4-18.
//

#ifndef KMINTFRAMEWORK_MANAGER_H
#define KMINTFRAMEWORK_MANAGER_H

#include <Movable_objects/State/state_object.h>
#include <city.h>

namespace kmint {
    class Manager: public state_object {
    private:
        city* stad;

    public:
        int dest_node_id;
        bool is_busy;
        double pause;
        double time;
        double wait;


        Manager(const graph &graph, node_id nid, const image &i, city* city):stad{city},pause{0},time{0}, wait{0},is_busy{false},state_object(graph,nid,i){
        };


        virtual void update(float dt, std::vector< board_piece*> &_board_pieces)override {
            float difference = dt - time;

            if(difference > 0.2){
                state_object::update( _board_pieces);
                time = dt;

            }else{
            }


        }

    void call_manager(int node_id){
        // cheack if manager is busy
        if(!is_busy){
            dest_node_id = node_id;
            //set busy
            is_busy = true;
            //set state
            this->set_state("go_to_bandlit");
        }else{
            std::cout<<"is busy"<< std::endl;
        }

    }


    };

}

#endif //KMINTFRAMEWORK_MANAGER_H
