#include <iostream>
#include <stdexcept>
#include "base_systems.h"
#include "board.h"
#include "graph.h"
#include "background.h"
#include "image.h"
#include "graph_bound_board_piece.h"
#include <fstream>
#include <Movable_objects/Cow/Cow.h>
#include <Movable_objects/Bunny/Bunny.h>
#include <circle.h>
#include "board_drawable.h"
#include "../a_star/a_star.h"

int main() {
    try {
        std::ifstream f { "/home/administrator/Desktop/KMINT/resources/graph.txt" };
        kmint::graph g { kmint::point{0.0f, 0.0f} };
        g.fill(f);

        kmint::base_systems base {};
        kmint::board s {};
        kmint::background b { kmint::image { "resources/Graph.png" } };
        kmint::graph_bound_board_piece rabbit { g, 1000, kmint::image { "resources/bunnelby.png", 0.33f } };
        kmint::graph_bound_board_piece meneer { g, 1000, kmint::image { "resources/meneerjanssen.png", 0.33f } };
        kmint::graph_bound_board_piece mevrouw { g, 1000, kmint::image { "resources/mevrouwjanssen.png", 0.33f } };
        kmint::Cow sheep{ g, 0, kmint::image { "resources/poochyena.png", 0.25f }};
        //kmint::Bunny t{ kmint::point{10,10},kmint::image { "resources/cow.png", 0.25f }};
        kmint::a_star search;
        kmint::node start = g[10];
        kmint::node end = g[1000];

        kmint::circle radius { rabbit, 20 };

        search.search(&g,&start, &end);
        s.add_board_piece(b);
        s.add_board_piece(g);

        s.add_board_piece(sheep);
        //s.add_board_piece(t);
        s.add_board_piece(rabbit);
        rabbit.update(10);

        s.play();
    }
    catch(const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }
    return 0;
}
