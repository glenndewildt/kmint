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

static double cohesionDistance { 100 };
static double alignmentDistance { 75 };
static double separationDistance { 50 };

static bool cohesionActive { true };
static bool alignmentActive { true };
static bool separationActive { true };

static double getCoordDifference(double x1, double y1, double x2, double y2) {
    return std::abs((x2 - x1) + (y2 - y1));
}

static double getCoordDifference(kmint::point left, kmint::point right) {
    return std::abs((left.x() - right.x()) + (left.y() - right.y()));
}

#endif //KMINTFRAMEWORK_GLOBALS_HPP