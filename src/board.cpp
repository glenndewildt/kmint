#include "board.h"
#include "point.h"
#include "board_piece.h"
#include "drawable.h"
#include <SDL2/SDL.h>
#include <graph_bound_board_piece.h>
#include <circle.h>

namespace kmint {
    board::board() : _window { "Hello World!", 1280, 720 },
                     _renderer { _window } {}

    void board::play() {
        bool playing = true;
        while(playing) {
            _renderer.clear();
            for(auto a : _board_pieces) {
                a->get_drawable().draw(_renderer);
                a->update(1.0);

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
