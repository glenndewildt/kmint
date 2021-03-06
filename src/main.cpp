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
#include <globals.hpp>

#include <fstream>
#include <Movable_objects/Cow/Cow.h>
#include <Movable_objects/Fan/Fan.h>
#include <circle.h>
#include <Movable_objects/State/state_object.h>
#include <Movable_objects/State/wandering_state.h>
#include <Movable_objects/State/sleep_state.h>
#include <Movable_objects/Sheep/Sheep.h>
#include <Movable_objects/State/retrieve_state.h>
#include <Movable_objects/Jansen/Mrs_Jansen.h>
#include <Movable_objects/Jansen/Miss_Jansen.h>
#include <city.h>
#include <functional>
#include <set>
#include <Movable_objects/Manager/Manager.h>
#include <Movable_objects/State/go_to_bandlit.h>
#include <Movable_objects/State/wait.h>
#include <Movable_objects/State/work.h>

#include "../a_star/a_star.h"

int main() {
    try {


        std::ifstream f { "/home/administrator/Desktop/KMINT/resources/graph.txt" };
        kmint::graph g { kmint::point{0.0f, 0.0f} };

        std::ifstream st { "/home/administrator/Desktop/KMINT/resources/stad.txt" };
        kmint::city c { kmint::point{0.0f, 0.0f} };
        c.fill(st);
        g.fill(f,&c);


        kmint::base_systems base {};
        kmint::board s {};
        kmint::background b { kmint::image { "resources/Graph.png" } };

//        kmint::Mrs_Jansen meneer { g, 5, kmint::image { "resources/meneerjanssen.png", 0.33f } };
//        kmint::Miss_Jansen mevrouw { g, 1570, kmint::image { "resources/mevrouwjanssen.png", 0.33f } };
        kmint::bandlit t1{ g,120,kmint::image { "resources/axel.png", 0.25f },&c, kmint::bandlit::AXEL};
        kmint::bandlit t2{ g,624,kmint::image { "resources/andre.png", 0.025f },&c, kmint::bandlit::ANDRE};
        kmint::bandlit t3{ g,1377,kmint::image { "resources/frans.png", 0.25f },&c, kmint::bandlit::FRANS};
        kmint::bandlit t4{ g,236,kmint::image { "resources/johnnie.png", 0.02f },&c, kmint::bandlit::JOHNNIE};
        kmint::Manager man {g,573,kmint::image { "resources/manager.png", 0.25f },&c};


        kmint::a_star search;
        kmint::node start = g[1];
        kmint::node end = g[100];
        //t.set_point(kmint::point{1000,100});

        //add states
        t1.add_state(new kmint::wandering_state(&t1),"wandering");
        t2.add_state(new kmint::wandering_state(&t2),"wandering");
        t3.add_state(new kmint::wandering_state(&t3),"wandering");
        t4.add_state(new kmint::wandering_state(&t4),"wandering");
        man.add_state(new kmint::wandering_state(&man),"wandering");

        t1.add_state(new kmint::wait(&t1),"wait");
        t2.add_state(new kmint::wait(&t2),"wait");
        t3.add_state(new kmint::wait(&t3),"wait");
        t4.add_state(new kmint::wait(&t4),"wait");

        t1.add_state(new kmint::work(&t1),"work");
        t2.add_state(new kmint::work(&t2),"work");
        t3.add_state(new kmint::work(&t3),"work");
        t4.add_state(new kmint::work(&t4),"work");

        man.add_state(new kmint::go_to_bandlit(&man),"go_to_bandlit");


        t1.add_state(new kmint::sleep_state(&t1),"sleep");
        t1.add_state(new kmint::retrieve_state(&t1),"retieve");

        t1.set_state("wandering");
        t2.set_state("wandering");
        t3.set_state("wandering");
        t4.set_state("wandering");
        man.set_state("wandering");




        //auto path = search.search(&g,start, end,0);


        s.add_board_piece(b);
        s.add_board_piece(g);
        s.add_board_piece(c);
        s.add_board_piece(g);

        s.add_board_piece(t1);
        s.add_board_piece(t2);
        s.add_board_piece(t3);
        s.add_board_piece(t4);
        s.add_board_piece(man);


        std::default_random_engine gen(rand() % 1000);
        std::uniform_int_distribution<int> xCord(10, 1270);
        std::uniform_int_distribution<int> yCord(10, 690);

        for (int i = 0; i < fansToSpawn; i++)
        {
            kmint::Fan *fan = new kmint::Fan { kmint::point { xCord(gen) , yCord(gen) }, kmint::image { "resources/xsfan.png", 1.00f } };
            s.add_board_piece(*fan);
        }

        s.play();
    }
    catch(const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }
    return 0;
}
