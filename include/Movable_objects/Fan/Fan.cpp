//
// Created by administrator on 21-12-17.
//

#include <image.h>
#include "Fan.h"
#include "globals.hpp"

using namespace kmint;

Fan::Fan(point location, const image &i) : free_roaming_board_piece { location }, _drawable { *this,i}, ata { 1 }, atf { 1 }, atj { 1 }, atx { 1 }, cohesion{1}, separation{1}, alignment{1}{

}

void kmint::Fan::update(float dt, std::vector<board_piece *> &_board_pieces) {
    double xDirection = 0;
    double yDirection = 0;

    scanForNearbyFans(_board_pieces);
    auto vec = Linal::G2D::Vector(xDirection, yDirection);

    for (auto coh : cohesionForces) {
        vec.x((vec.x() - coh.x()) * cohesion);
        vec.y((vec.y() - coh.y()) * cohesion);
    }

    for (auto sep : separationForces) {
        vec.x((vec.x() - sep.x()) * separation);
        vec.y((vec.y() - sep.y()) * separation);
    }

    for (auto ali : alignmentForces) {
        vec.x((vec.x() - ali.x()) * alignment);
        vec.y((vec.y() - ali.y()) * alignment);
    }

    vec = vec.GetUnitVector();
    auto loc = location();

    auto newloc = kmint::point{ round(vec.x()) + loc.x(), round(vec.y()) + loc.y() };

    if (newloc.x() < 10) newloc.x(10); else if (newloc.x() > 1270) newloc.x(1270);
    if (newloc.y() < 10) newloc.y(10); else if (newloc.y() > 710) newloc.y(710);

    set_point(newloc);

    setVelocity(vec);

    cohesionForces.clear();
    separationForces.clear();
    alignmentForces.clear();
}

/******************************
* SCANNING OF THE NEARBY AREA *
******************************/
void Fan::scanForNearbyFans(std::vector< board_piece*> &_board_pieces)
{
    auto loc = location();

    for (auto bp : _board_pieces)
    {
        if (bp == this) continue; // Skip yourself

        if (auto fo = dynamic_cast<kmint::Fan*>(bp))
        {
            if (!fo->isAlive) continue; // Leave the dead alone

            auto foLoc = fo->location();
            auto dist = getCoordDifference(foLoc, loc);

            if (cohesionActive && dist <= cohesionDistance) {
                cohesionForces.push_back({loc.x() - foLoc.x(), loc.y() - foLoc.y()});
            }

            if (separationActive && dist <= separationDistance) {
                separationForces.push_back({dist - (loc.x() - foLoc.x()), dist - ( loc.y() - foLoc.y())});
            }

            if (alignmentActive && dist <= alignmentDistance) {
                alignmentForces.push_back(fo->getVelocity());
            }
        }
    }
}

/***********************
* CALCULATION OF STUFF *
***********************
Linal::G2D::Vector GetCohesionVec(std::vector< board_piece*> _board_pieces) {
    auto loc = location();
    auto vec = Linal::G2D::Vector(loc.x(), loc.y());

    int sumCount = 0;
    Linal::G2D::Vector vecSum;
    for (auto bp : _board_pieces)
    {
        if (auto foreignObject = dynamic_cast<kmint::Fan*>(bp))
        {
            //if (foreignObject->hasDied()) continue;

            auto targetLoc = bp->location();
            if (targetLoc.x() == loc.x() && targetLoc.y() == loc.y())
                continue;

            auto targetVec = Linal::G2D::Vector(targetLoc.x(), targetLoc.y()) ;

            auto diff = (targetLoc - loc);
            if (std::abs(diff.x()) + std::abs(diff.y()) > cohesionDistance)
                continue;

            vecSum = vecSum + targetVec;
            sumCount++;
        }
    }

    if (sumCount > 0) {
        vecSum = vecSum / sumCount;
        vecSum.x(vecSum.x() - loc.x());
        vecSum.y(vecSum.y() - loc.y());
        return vecSum;
    }

    return Linal::G2D::Vector(0, 0);
}

Linal::G2D::Vector GetSeparationVec(std::vector< board_piece*> _board_pieces) {
    auto loc = location();
    auto vec = Linal::G2D::Vector(loc.x(), loc.y());

    auto targetVecSum = Linal::G2D::Vector(0, 0);
    int count = 0;
    for (auto bp : _board_pieces)
    {
        if (auto foreignObject = dynamic_cast<kmint::Fan*>(bp))
        {
            //if (foreignObject->hasDied()) continue;

            auto targetLoc = bp->location();
            if (loc.x() == targetLoc.x() && loc.y() == targetLoc.y())
                continue;

            auto targetVec = Linal::G2D::Vector(targetLoc.x(), targetLoc.y()) ;

            auto diffVec = targetVec - vec;

            if (std::abs(diffVec.x()) + std::abs(diffVec.y()) < separationDistance)
            {
                targetVecSum = targetVecSum + targetVec;
                count++;
            }

        }
    }

    if (count > 0)
    {
        auto diffVec = (targetVecSum / count) - vec;
        return (vec - (targetVecSum / count)).GetUnitVector() * (separationDistance + (std::abs(diffVec.x() + std::abs(diffVec.y()))));
    }


    return Linal::G2D::Vector(0, 0);
}

Linal::G2D::Vector GetAlignmentVec(std::vector< board_piece*> _board_pieces) {
    auto loc = location();
    auto vec = Linal::G2D::Vector(loc.x(), loc.y());

    int sumCount = 0;
    Linal::G2D::Vector vecSum;
    for (auto bp : _board_pieces)
    {
        if (auto foreignObject = dynamic_cast<kmint::Fan*>(bp))
        {
            //if (bunny->hasDied()) continue;

            auto targetLoc = foreignObject->location();
            if (targetLoc.x() == loc.x() && targetLoc.y() == loc.y())
                continue;

            auto diff = (targetLoc - loc);
            if (std::abs(diff.x()) + std::abs(diff.y()) > alignmentDistance)
                continue;

            //vecSum = vecSum + foreignObject->GetVelocity();
            sumCount++;
        }
    }

    if (sumCount > 0) {
        vecSum = (vecSum / sumCount).GetUnitVector();
        vecSum = vecSum + vec;

        return vecSum;
    }

    return Linal::G2D::Vector(0, 0);
}

/**********************
* GETTERS AND SETTERS *
**********************/
Linal::G2D::Vector Fan::getVelocity() const {
    return velocity;
}

Fan& Fan::setVelocity(Linal::G2D::Vector velocity) {
    this->velocity = velocity;
    return *this;
}

double Fan::getAttractionToAndre() const {
    return ata;
}

Fan& Fan::setAttractionToAndre(double ata) {
    this->ata = ata;
    return *this;
}

double Fan::getAttractionToAxel() const {
    return atx;
}

Fan& Fan::setAttractionToAxel(double atx) {
    this->atx = atx;
    return *this;
}

double Fan::getAttractionToFrans() const {
    return atf;
}

Fan& Fan::setAttractionToFrans(double atf) {
    this->atf = atf;
    return *this;
}

double Fan::getAttractionToJohnnie() const {
    return atj;
}

Fan& Fan::setAttractionToJohnnie(double atj) {
    this->atj = atj;
    return *this;
}

double Fan::getCohesion() const {
    return cohesion;
}

Fan& Fan::setCohesion(double cohestion) {
    this->cohesion = cohesion;
    return *this;
}

double Fan::getSeparation() const {
    return separation;
}

Fan& Fan::setSeparation(double separation) {
    this->separation = separation;
    return *this;
}

double Fan::getAlignment() const {
    return alignment;
}

Fan& Fan::setAlignment(double alignment) {
    this->alignment = alignment;
    return *this;
}