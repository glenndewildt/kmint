//
// Created by administrator on 6-4-18.
//

#ifndef KMINTFRAMEWORK_GLOBALS_HPP
#define KMINTFRAMEWORK_GLOBALS_HPP

#include <cmath>

static bool attractedToAndreActive { false };
static bool attractedToAxelActive { false };
static bool attractedToFransActive { false };
static bool attractedToJohnnieActive { false };

static bool cohesionActive { true };
static bool separationActive { true };
static bool alignmentActive { false };

static double getCoordDifference(double x1, double y1, double x2, double y2) {
    return std::abs((x2 - x1) + (y2 - y1));
}

#endif //KMINTFRAMEWORK_GLOBALS_HPP