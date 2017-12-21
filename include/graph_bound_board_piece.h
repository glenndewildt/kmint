#ifndef _KMINT_GRAPH_BOUND_ACTOR_H
#define _KMINT_GRAPH_BOUND_ACTOR_H

#include "graph.h"
#include "image_drawable.h"

namespace kmint {
    class graph_bound_board_piece : public board_piece {
        const graph* _graph;
        node_id _node_id;
        image_drawable _drawable;
    public:
        graph_bound_board_piece(const graph &graph, node_id nid, const image &i) : _graph { &graph }, _node_id { nid } , _drawable { *this, i } {};
        point location() const override { return get_graph()[_node_id].location(); }
        const drawable& get_drawable() const override { return _drawable; }

        const graph& get_graph() const { return *_graph; }
        node_id get_node_id() const { return _node_id; }
        void set_node_id(node_id nid)  { _node_id = nid; }



    };
}

#endif
