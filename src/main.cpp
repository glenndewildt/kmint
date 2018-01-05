#include <iostream>
#include <random>
#include <algorithm>
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
#include <Movable_objects/Sheep/state_object.h>
#include <Movable_objects/Sheep/wandering_state.h>
#include <Movable_objects/Sheep/sleep_state.h>
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

        kmint::graph_bound_board_piece meneer { g, 5, kmint::image { "resources/meneerjanssen.png", 0.33f } };
        kmint::graph_bound_board_piece mevrouw { g, 1570, kmint::image { "resources/mevrouwjanssen.png", 0.33f } };
        kmint::Cow sheep{ g, 0, kmint::image { "resources/poochyena.png", 0.25f }};
        kmint::state_object t{ g,447,kmint::image { "resources/cow.png", 0.25f }};
        kmint::a_star search;
        kmint::node start = g[445];
        kmint::node end = g[460];
        //t.set_point(kmint::point{1000,100});

        //add states
        t.add_state(new kmint::wandering_state(&t),"wandering");
        t.add_state(new kmint::sleep_state(&t),"sleep");

        t.set_state("wandering");

        search.search(&g,start, end);
        s.add_board_piece(b);
        s.add_board_piece(g);
        s.add_board_piece(meneer);
        s.add_board_piece(mevrouw);

        s.add_board_piece(sheep);
        s.add_board_piece(t);

        kmint::Bunny bunny { kmint::point { 10, 20 }, kmint::image { "resources/bunnelby.png", 0.33f } };
        //s.add_board_piece(bunny);

        std::default_random_engine gen(rand());
        std::uniform_int_distribution<int> xCord(10, 1270);
        std::uniform_int_distribution<int> yCord(10, 690);

        for (int i = 0; i < 100; i++)
        {
            kmint::Bunny *bunny = new kmint::Bunny { kmint::point { xCord(gen) , yCord(gen) }, kmint::image { "resources/bunnelby.png", 0.33f } };
            s.add_board_piece(*bunny);
        }

        s.play();
    }
    catch(const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }
    return 0;
}
