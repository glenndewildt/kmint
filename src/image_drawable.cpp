#include "image_drawable.h"
#include "board_piece.h"
#include <iostream>
#include "renderer.h"

namespace kmint {
    image_drawable::image_drawable(const board_piece &act, const image& i) : drawable { act }, _image { i } {
    }

    void image_drawable::draw(const renderer &r) const {
        r.draw_image(get_board_piece().location(), _image);
    }
}
