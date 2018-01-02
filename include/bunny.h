//
// Created by administrator on 1-1-18.
//

#ifndef KMINTFRAMEWORK_BUNNY_H
#define KMINTFRAMEWORK_BUNNY_H

#include <graph_bound_board_piece.h>
#include <iostream>

namespace kmint {

    class Bunny : public graph_bound_board_piece {
    public:

        Bunny(const graph &graph, node_id nid, const image &i) : graph_bound_board_piece(graph, nid, i) {};
        Bunny(const graph &graph, node_id nid, const image &i, double ats, double atw, double c, double s, double a)
                : graph_bound_board_piece(graph, nid, i), attractedToSheep(ats), attractedToWater(atw), cohesion(c), separation(s), alignment(a)
        {};

        virtual void update(float dt) {

        }

    private:
        double attractedToSheep;
        double attractedToWater;
        double cohesion;
        double separation;
        double alignment;
    };
}

#endif //KMINTFRAMEWORK_BUNNY_H
