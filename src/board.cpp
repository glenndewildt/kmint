#include "board.h"
#include "point.h"
#include "board_piece.h"
#include "drawable.h"
#include "FanSpawner.h"
#include <SDL2/SDL.h>
#include <graph_bound_board_piece.h>
#include <circle.h>
#include <Movable_objects/Bunny/Bunny.h>
#include <algorithm>
#include <ctime>
#include <fstream>

#include <unistd.h>

namespace kmint {
    board::board() : _window { "Hello World!", 1280, 720 },
                     _renderer { _window } {}

    bool hasDied(kmint::board_piece* i)
    {
        if (auto bunny = dynamic_cast<kmint::Bunny*>(i)) {
            return true; //return bunny->hasDied();
        }

        return false;
    }

    void board::play() {
        bool playing = true;


        // timer variable
        std::clock_t start;
        double duration;
        //start time
        start = std::clock();

        /* Your algorithm here */

        int frame { 0 };

        while(playing) {
            frame++;
            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

            _renderer.clear();


            // Only remove on new poolCycle
            // @TODO: move and split to a onEntry and onExit on the sleep state of the dog
            if (frame % 100 == 0) {
                FanSpawner bs(_board_pieces);
                auto newPool = bs.GetSpawnPool();

                auto q = std::remove_if(_board_pieces.begin(), _board_pieces.end(), hasDied);
                _board_pieces.erase(q, _board_pieces.end());

                for (auto &nb : newPool)
                {
                    _board_pieces.push_back(&*nb);
                }
            }

                for (auto a : _board_pieces) {
                    a->update(duration, _board_pieces);

                    if (auto bunny = dynamic_cast<kmint::Bunny *>(a)) {
                        if (!bunny->hasDied()) {
                            a->get_drawable().draw(_renderer);
                        }
                    } else {
                        a->get_drawable().draw(_renderer);
                    }
                }

            _renderer.render();




            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                playing = (e.type != SDL_QUIT);
            }

            //sleep(1);
        }
    }

};
