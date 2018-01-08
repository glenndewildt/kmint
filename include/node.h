#ifndef _KMINT_NODE_H
#define _KMINT_NODE_H

#include <vector>
#include "point.h"
#include "edge.h"
#include "color.h"

namespace kmint {
    class node {
        point _location;
        int _id;
        int type;
        std::vector<edge> _edges;

    public:
        color _color;

        node(point location, int id) : _location {location}, _id {id}, _edges {}, _color{ 0xff, 0x00, 0x00 } {}
        int id() const noexcept { return _id; }
        point location() const noexcept { return _location; }
        void add_edge(edge e) { _edges.push_back(e); }
        decltype(auto) begin() const noexcept { return _edges.begin(); }
        decltype(auto) end() const noexcept { return _edges.end(); }
        const bool operator < ( const node &r ) const{
            return ( true );
        }
    };
}

#endif
