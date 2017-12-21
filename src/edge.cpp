#include "edge.h"
#include "node.h"
#include "point.h"

namespace kmint {
    float edge::distance() const {
        return kmint::distance(from().location(), to().location())*weight();
    }
}
