//
// Created by administrator on 13-3-18.
//

#ifndef KMINTFRAMEWORK_CITY_DRAWABLE_H
#define KMINTFRAMEWORK_CITY_DRAWABLE_H

#include "drawable.h"

namespace kmint{
    class city;
class city_drawable : public drawable {
    const city& get_graph() const;
public:
    city_drawable(const city& g);
    void draw(const renderer &r) const override;
};

}


#endif //KMINTFRAMEWORK_CITY_DRAWABLE_H
