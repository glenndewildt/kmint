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
#include <Movable_objects/Bunny.h>
#include "board_drawable.h"

int main() {
    try {
        std::ifstream f { "/home/administrator/Desktop/KMINT/resources/graph.txt" };
        kmint::graph g { kmint::point{0.0f, 0.0f} };
        g.fill(f);




        kmint::base_systems base {};
        kmint::board s {};
        kmint::background b { kmint::image { "resources/Sand.png" } };
        kmint::graph_bound_board_piece hare { g, 1000, kmint::image { "resources/hare.png", 0.33f } };
         kmint::Cow cow{ g, 0, kmint::image { "resources/cow.png", 0.25f }};
        kmint::point p{10,10};
        s.add_board_piece(b);
        s.add_board_piece(g);
        s.add_board_piece(cow);
        s.add_board_piece(hare);
            hare.update(10);


        s.play();
    }
    catch(const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }
    return 0;
}
