#ifndef _KMINT_GRAPH_H
#define _KMINT_GRAPH_H

#include "node.h"
#include "point.h"
#include "free_roaming_board_piece.h"
#include "graph_drawable.h"
#include "city.h"
#include <unordered_map>
#include <vector>
#include <istream>
#include <iostream>

namespace kmint {

    using node_id = std::vector<node>::size_type;
    class graph : public free_roaming_board_piece {
        std::vector<node> _nodes;
        graph_drawable _drawable;
        bool mapAnalized = false;
        std::vector<std::vector<bool>> mapAnalysis;
    public:
        graph(point location) : free_roaming_board_piece { location }, _nodes {}, _drawable { *this } {};
        void fill(std::istream &is, city* city);
        const drawable &get_drawable() const override { return _drawable; }
        std::vector<std::vector<bool>> GetMapAnalysis() {
            if (!mapAnalized) {
                AnalysizeMapStructure();
            }
            return mapAnalysis;
        }
        decltype(auto) begin() { return _nodes.begin(); }
        decltype(auto) begin() const { return _nodes.begin(); }
        decltype(auto) end() { return _nodes.end(); }
        decltype(auto) end() const { return _nodes.end(); }
        decltype(auto) num_nodes() const { return _nodes.size(); }
        decltype(auto) operator[](node_id id) const { return _nodes[id]; }
    private:
        void AnalysizeMapStructure() {
            int rowSize = 1280 / 20;
            int colSize =  720 / 20;
            bool initialValue = false;

            mapAnalysis.resize(colSize, std::vector<bool>(rowSize, initialValue));

            std::cout << "analyzing the map" << std::endl;
            for (auto n : _nodes)
            {
                auto loc = n.location();
                auto xCord = (loc.x() - 10) / 20;
                auto yCord = (loc.y() - 10) / 20;

                mapAnalysis[yCord][xCord] = true;
            }

            std::cout << "finished analyzing" << std::endl;
            mapAnalized = true;
        }
    };
}

#endif
