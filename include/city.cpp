//
// Created by administrator on 13-3-18.
//

#include "city.h"
namespace kmint {
    void city::fill(std::istream &is) {
        bool reading_nodes = true;
        for(std::string s; std::getline(is, s);) {
            if (s == "") {
                reading_nodes = false;
                continue;
            }else{
                char c;
                while (is.get(c)){
                    point p{10,10};
                    _nodes.emplace_back(p,num_nodes());

                }

            }


        }

    }
}
