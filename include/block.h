//
// Created by administrator on 13-3-18.
//

#ifndef KMINTFRAMEWORK_BLOCK_H
#define KMINTFRAMEWORK_BLOCK_H
#include "point.h"
#include "color.h"
namespace kmint {

class block{
    point _location;
    int _id;
    int type;

public:
    int weight;

    color _color;
    block(point location, int id, color col,int weight) : _location {location}, _id {id}, _color{col }, weight{weight}{}
    int id() const noexcept { return _id; }
    point location() const noexcept { return _location; }

};
}


#endif //KMINTFRAMEWORK_BLOCK_H
