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
    color _color;
    block(point location, int id) : _location {location}, _id {id}, _color{ 0xff, 0x00, 0x00 } {}
    int id() const noexcept { return _id; }
    point location() const noexcept { return _location; }

};
}


#endif //KMINTFRAMEWORK_BLOCK_H
