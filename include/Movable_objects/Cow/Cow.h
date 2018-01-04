//
// Created by administrator on 19-12-17.
//

#ifndef KMINTFRAMEWORK_COW_H
#define KMINTFRAMEWORK_COW_H

#include <graph_bound_board_piece.h>
#include <iostream>

namespace kmint {

    class Cow : public graph_bound_board_piece{
    public:

        Cow(const graph &graph, node_id nid, const image &i):graph_bound_board_piece(graph, nid, i){};

         void update(float dt) {
            std::cout << "update cow" <<std::endl;
            set_node_id({get_node_id()+1});
            

        }


    };
}


#endif //KMINTFRAMEWORK_COW_H
