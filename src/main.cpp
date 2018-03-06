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
#include <Movable_objects/State/state_object.h>
#include <Movable_objects/State/wandering_state.h>
#include <Movable_objects/State/sleep_state.h>
#include <Movable_objects/Sheep/Sheep.h>
#include <Movable_objects/State/retrieve_state.h>
#include <Movable_objects/Jansen/Mrs_Jansen.h>
#include <Movable_objects/Jansen/Miss_Jansen.h>

#include "../a_star/a_star.h"

int main() {
    try {
        std::ifstream f { "/home/administrator/Desktop/KMINT/resources/graph.txt" };
        kmint::graph g { kmint::point{0.0f, 0.0f} };
        g.fill(f);

        kmint::base_systems base {};
        kmint::board s {};
        kmint::background b { kmint::image { "resources/Graph.png" } };

        kmint::Mrs_Jansen meneer { g, 5, kmint::image { "resources/meneerjanssen.png", 0.33f } };
        kmint::Miss_Jansen mevrouw { g, 1570, kmint::image { "resources/mevrouwjanssen.png", 0.33f } };
        kmint::bandlit t{ g,0,kmint::image { "resources/poochyena.png", 0.25f }};
        kmint::a_star search;
        kmint::node start = g[445];
        kmint::node end = g[457];
        //t.set_point(kmint::point{1000,100});

        //add states
        t.add_state(new kmint::wandering_state(&t),"wandering");
        t.add_state(new kmint::sleep_state(&t),"sleep");
        t.add_state(new kmint::retrieve_state(&t),"retieve");

        t.set_state("wandering");

        search.search(&g,start, end);
        s.add_board_piece(b);
        s.add_board_piece(g);
        s.add_board_piece(meneer);
        s.add_board_piece(mevrouw);

        s.add_board_piece(t);

        std::default_random_engine gen(rand() % 1000);
        std::uniform_int_distribution<int> xCord(10, 1270);
        std::uniform_int_distribution<int> yCord(10, 690);

        for (int i = 0; i < 20; i++)
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
