//
// Created by administrator on 21-12-17.
//

#include "a_star.h"
#include <climits>
#include <set>
#include <iostream>
#include<bits/stdc++.h>


namespace kmint {

    void a_star::search( graph* begin, node start, node end, bool debug) {
        std::vector<node> openList;      // Make it priority-able with the F score
        std::vector<node> closedList;

        openList.emplace_back(start);

        node currentNode = start;

        /**
         * F Score = Score for square
         * G score = cost from start to square
         * H score = estimated cost from square
         *
         * H is calculated by pixel difference between the two points using the math.abs function
         * G is calculated by shortest path
         */

        do {
            // @PSEUDO, get node with lowest heuristisk

            // @PSEUDO add this node to closedList
            // @PSEUDO remove this node from openList

            if (&currentNode == &end) {
                break; // @TODO?? shouldn't this by a return, i never understood this
            }

            // std::vector connections = currentNode.getAllConnectedNodes();

            for (auto connection : openList) { // TODO replace openlist by connections
                //if (closedList.has(connection)) {
                //    continue;
                //}

                /*
                 if (!openlist.has(connection)) {
                    calculate F score
                    add it to the openlist
                 } else {
                    test if F score get lower by current G score, if yes update parent
                 }
                */
            }
        } while (!openList.empty());

        // THERE IS NO PATH< OH HELP!
    }

    void a_star::search( graph* begin, node start, node end) {
        std::unordered_map<int, int> dist;

        for (auto& j:*begin) {

            dist[j.id()] = INT_MAX;
        }

        std::set<std::pair<int, node>> s;
        int current_node_id = start.id();

        s.insert(std::make_pair(0, start));

        while (current_node_id != end.id()) {
            // find the pair at the front
            auto p = *(s.begin());
            auto node = p.second;
            int node_distance = p.first;

            for (auto& j:*begin) {
                if(j.id() == node.id()){
                    j._color = color { 0xff, 0xff, 0xff } ;

                }

            }

            s.erase(s.begin());


            //iterate over neibeurs of the current node

            for (auto& childpair:node) {
                auto var = dist[childpair.from().id()];
                int d = (int)sqrt(pow(childpair.to().location().x() - end.location().x(), 2) + pow(childpair.to().location().y() - end.location().y(), 2));
                if (node_distance + childpair.weight()+d < dist[childpair.to().id()]) {

                    // set update is not possible of node
                    // we remove the old pair
                    auto dest = childpair.to();
                    auto f = s.find(std::make_pair(dist[dest.id()], dest));
                    if (f != s.end()) {
                        s.erase(f);
                    }
                    // insert new pair
                    dist[dest.id()] = node_distance + childpair.weight();


                    s.insert(std::make_pair(dist[dest.id()]+d, dest));

                }

            }

current_node_id = p.second.id();
        }
        for (auto d : dist) {
            std::cout << d.first << " is locatetd at distance of " << d.second << std::endl;
        }

    }
}