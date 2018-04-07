//
// Created by administrator on 6-4-18.
//

#ifndef KMINTFRAMEWORK_GLOBALS_HPP
#define KMINTFRAMEWORK_GLOBALS_HPP

#include <cmath>

static int fansToSpawn { 100 };

static bool attractedToAndreActive { true };
static bool attractedToAxelActive { true };
static bool attractedToFransActive { true };
static bool attractedToJohnnieActive { true };
static bool heresjohnniemode { true };

static double bandmemberDistance { 1000 };
static double johnniedeadzone { 15 };
static double cohesionDistance { 75 };
static double alignmentDistance { 65 };
static double separationDistance { 1500 };

static bool cohesionActive { true };
static bool alignmentActive { true };
static bool separationActive { true };


static double getCoordDifference(double x1, double y1, double x2, double y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

static double getCoordDifference(kmint::point left, kmint::point right) {
    return std::abs(left.x() - right.x()) + std::abs(left.y() - right.y());
}

#endif //KMINTFRAMEWORK_GLOBALS_HPP