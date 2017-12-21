#ifndef _KMINT_IMAGE_DRAWABLE_H
#define _KMINT_IMAGE_DRAWABLE_H

#include "drawable.h"
#include "image.h"

namespace kmint {
    class renderer;
    class image_drawable : public drawable {
        image _image;
    public:
        image_drawable(const board_piece& act, const image &i);
        void draw(const renderer &r) const override;
    };
}
#endif
