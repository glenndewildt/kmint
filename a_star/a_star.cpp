//
// Created by administrator on 21-12-17.
//

#include "a_star.h"
#include <climits>
#include <set>
#include <iostream>
#include<bits/stdc++.h>


namespace kmint {

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