//
// Created by administrator on 13-3-18.
//

#include "city_drawable.h"
#include "renderer.h"
#include "city.h"

namespace kmint{

const city& city_drawable::get_graph() const {
    return static_cast<const city&>(get_board_piece());

}

    city_drawable::city_drawable(const city& g) : drawable(g) {
}

void city_drawable::draw(const renderer &r) const {
    auto graph_loc = get_graph().location();

    // draw edges first
    r.set_color(color { 0xff, 0xff, 0xff } );


    // draw nodes

    for(const auto &n : get_graph()) {
        r.set_color(n._color);

        auto x = graph_loc.x() + n.location().x();
        auto y = graph_loc.y() + n.location().y();

        r.draw_rect({x , y  },
                    {x + 20, y + 20 });


    }
}
}