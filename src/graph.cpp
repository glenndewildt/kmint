#include "graph.h"
#include "point.h"
#include "edge.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <city.h>

namespace kmint {
    void graph::fill(std::istream &is, city* city) {
        bool reading_nodes = true;
        for(std::string s; std::getline(is, s);) {
            if (s == "") {
                reading_nodes = false;
                continue;
            }

            std::istringstream iss { s };
            if (reading_nodes) {
                point p;
                if (iss >> p) {
                    _nodes.emplace_back(p, num_nodes());
                }
                else {
                    throw std::runtime_error { "Error while reading node: " + s };
                }
            }
            else {
                int from;
                int to;
                float weight;
                if (iss >> from && iss >> to  && iss >> weight) {
                    auto &from_node = _nodes.at(from);

                    for(auto& locations : city->_nodes){
                        if((locations.location().x() -20 < this->location().x())&& (locations.location().x() +20 > this->location().x()) && (locations.location().x() -20 < this->location().y())&& (locations.location().y() +20 > this->location().y())){
                            weight+=locations.weight;
                            break;
                        }
                    }
                    from_node.add_edge({from_node, _nodes.at(to), weight});
                }
                else {
                    throw std::runtime_error { "Error while reading edge: " + s };
                }
            }
        }
        
    }
}
