#include "board.h"
#include "point.h"
#include "board_piece.h"
#include "drawable.h"
#include <SDL2/SDL.h>

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
            }
            _renderer.render();

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                playing = (e.type != SDL_QUIT);
            }
        }
    }
};
