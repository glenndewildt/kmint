#ifndef _KMINT_GRAPH_H
#define _KMINT_GRAPH_H

#include "node.h"
#include "point.h"
#include "free_roaming_board_piece.h"
#include "graph_drawable.h"
#include <unordered_map>
#include <vector>
#include <istream>

namespace kmint {
    using node_id = std::vector<node>::size_type;
    class graph : public free_roaming_board_piece {
        std::vector<node> _nodes;
        graph_drawable _drawable;
    public:
        graph(point location) : free_roaming_board_piece { location }, _nodes {}, _drawable { *this } {};
        void fill(std::istream &is);
        const drawable &get_drawable() const override { return _drawable; }
        decltype(auto) begin() { return _nodes.begin(); }
        decltype(auto) begin() const { return _nodes.begin(); }
        decltype(auto) end() { return _nodes.end(); }
        decltype(auto) end() const { return _nodes.end(); }
        decltype(auto) num_nodes() const { return _nodes.size(); }
        decltype(auto) operator[](node_id id) const { return _nodes[id]; }
    };
}

#endif
