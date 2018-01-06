//
// Created by administrator on 6-1-18.
//

#ifndef KMINTFRAMEWORK_MISS_JANSEN_H
#define KMINTFRAMEWORK_MISS_JANSEN_H


#include <Movable_objects/State/state_object.h>
#include <bunny.h>

namespace kmint {
        class Miss_Jansen: public state_object {
        private:

        public:
            int pause;
            int time;
            int wait;


            Miss_Jansen(const graph &graph, node_id nid, const image &i):pause{0},time{0}, wait{0},state_object(graph,nid,i){
            };
            virtual void update(float dt, std::vector< board_piece*> &_board_pieces)override {
                int count = 0;
                //check condition if near by bunny
                for (auto bp : _board_pieces) {
                    if (dynamic_cast<Bunny *>(bp)) {

                        auto loc = bp->location();

                        auto diff = (this->location() - loc);

                        if (std::abs(diff.x()) + std::abs(diff.y()) < 30) {
                            count++;
                        }


                    }

                }
                if (count < 1) {
                    set_node_id({get_node_id() -1});
                }

                int difference = dt - pause;

            }


        };
    }


#endif //KMINTFRAMEWORK_MISS_JANSEN_H
