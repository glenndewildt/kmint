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

        kmint::Bunny rabbit1 { kmint::point { 380, 360}, kmint::image { "resources/bunnelby.png", 0.33f } };
        kmint::Bunny rabbit2 { kmint::point { 120, 100}, kmint::image { "resources/bunnelby.png", 0.33f } };
        kmint::Bunny rabbit3 { kmint::point { 850, 120}, kmint::image { "resources/bunnelby.png", 0.33f } };
        kmint::Bunny rabbit4 { kmint::point { 855, 122}, kmint::image { "resources/bunnelby.png", 0.33f } };

        kmint::Bunny rabbit5 { kmint::point { 845, 118}, kmint::image { "resources/bunnelby.png", 0.33f } };

        kmint::graph_bound_board_piece meneer { g, 5, kmint::image { "resources/meneerjanssen.png", 0.33f } };
        kmint::graph_bound_board_piece mevrouw { g, 1570, kmint::image { "resources/mevrouwjanssen.png", 0.33f } };
        kmint::Cow sheep{ g, 0, kmint::image { "resources/poochyena.png", 0.25f }};
        //kmint::Cow t{ kmint::point{10,10},kmint::image { "resources/cow.png", 0.25f }};
        kmint::a_star search;
        kmint::node start = g[445];
        kmint::node end = g[460];
        //t.set_point(kmint::point{1000,100});

        search.search(&g,start, end);
        s.add_board_piece(b);
        s.add_board_piece(g);
        s.add_board_piece(meneer);
        s.add_board_piece(mevrouw);

        s.add_board_piece(sheep);
        //s.add_board_piece(t);
        s.add_board_piece(rabbit1);
        s.add_board_piece(rabbit2);
        s.add_board_piece(rabbit3);
        s.add_board_piece(rabbit4);
        s.add_board_piece(rabbit5);

        s.play();
    }
    catch(const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }
    return 0;
}
