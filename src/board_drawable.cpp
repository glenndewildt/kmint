//
// Created by administrator on 18-12-17.
//

#include "board_drawable.h"
#include "renderer.h"

namespace kmint {

    void board_drawable::draw(const renderer& r) const {

        r.draw_rect({10,10},{10,10});
    }
}
