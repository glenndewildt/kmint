#ifndef _KMINT_CIRCLE_H
#define _KMINT_CIRCLE_H
#include "drawable.h"
namespace kmint {
    class renderer;
    class circle : public drawable {
        int _radius;
    public:
        circle(const board_piece& actr, int radius) : drawable { actr }, _radius{radius} {}
        void draw(const renderer &r) const override;
    };
}
#endif
