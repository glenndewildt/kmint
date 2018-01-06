#include "board.h"
#include "point.h"
#include "board_piece.h"
#include "drawable.h"
#include <SDL2/SDL.h>
#include <graph_bound_board_piece.h>
#include <circle.h>
#include <ctime>

namespace kmint {
    board::board() : _window { "Hello World!", 10, 10 },
                     _renderer { _window } {}

    void board::play() {
        bool playing = true;

        // timer variable
        std::clock_t start;
        double duration;
        //start time
        start = std::clock();

        /* Your algorithm here */



        while(playing) {
            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

            _renderer.clear();
            for(auto a : _board_pieces) {
                a->update(duration, _board_pieces);
                a->get_drawable().draw(_renderer);

                /*if (dynamic_cast<kmint::graph_bound_board_piece*>(a))
                {
                    kmint::circle radius { *a, 500 };
                    _renderer.set_color(color(255, 0, 0, 255));
                    std::cout << "rendered cirlce";
                    radius.draw(_renderer);
                }*/
            }
            _renderer.render();

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                playing = (e.type != SDL_QUIT);
            }
        }
    }

};
