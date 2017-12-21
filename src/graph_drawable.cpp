#include "graph_drawable.h"
#include "board_piece.h"
#include "graph.h"
#include "point.h"
#include "edge.h"
#include "color.h"
#include "renderer.h"

namespace kmint {

    constexpr float node_width = 5.0f;
    constexpr float node_half_width = node_width / 2.0f;

    const graph& graph_drawable::get_graph() const {
        return static_cast<const graph&>(get_board_piece());

    }

    graph_drawable::graph_drawable(const graph& g) : drawable(g) {
    }

    void graph_drawable::draw(const renderer &r) const {
        auto graph_loc = get_graph().location();

        // draw edges first
        r.set_color(color { 0xff, 0xff, 0xff } );
        for(const auto &n : get_graph()) {
            auto x = graph_loc.x() + n.location().x();
            auto y = graph_loc.y() + n.location().y();

            for(auto &e : n) {
                auto to_x = graph_loc.x() + e.to().location().x();
                auto to_y = graph_loc.y() + e.to().location().y();
                r.draw_line({x, y}, {to_x, to_y});
            }
        }

        // draw nodes

        r.set_color(color { 0xff, 0x00, 0x00 } );
        for(const auto &n : get_graph()) {
            auto x = graph_loc.x() + n.location().x();
            auto y = graph_loc.y() + n.location().y();

            r.draw_rect({x - node_half_width, y - node_half_width },
                        {x + node_half_width, y + node_half_width });


        }
    }
}
