#include "board.h"
#include "point.h"
#include "board_piece.h"
#include "drawable.h"
#include <SDL2/SDL.h>
#include <graph_bound_board_piece.h>
#include <circle.h>
#include "isOnWater.h"
#include <Movable_objects/Bunny/Bunny.h>
#include <algorithm>

namespace kmint {
    board::board() : _window { "Hello World!", 1280, 720 },
                     _renderer { _window } {}

    bool hasDied(kmint::Bunny* bunny)
    {
        return bunny->hasDied();
    }

    void board::play() {
        bool playing = true;

        while(playing) {
            _renderer.clear();

            auto q = std::remove_if(_board_pieces.begin(), _board_pieces.end(), hasDied);
            _board_pieces.erase(q, _board_pieces.end());

            for(auto a : _board_pieces) {
                a->update(1.0, _board_pieces);

                if (auto bunny = dynamic_cast<kmint::Bunny*>(a)) {
                    if (!bunny->hasDied()) {
                        a->get_drawable().draw(_renderer);
                    }
                }
                else
                {
                    a->get_drawable().draw(_renderer);
                }


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
