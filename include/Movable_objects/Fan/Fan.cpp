//
// Created by administrator on 21-12-17.
//

#include <image.h>
#include "Fan.h"
#include "globals.hpp"

using namespace kmint;

Redefined::Redefined(point location, const image &i) : free_roaming_board_piece { location }, _drawable { *this,i}, ata { 1 }, atf { 1 }, atj { 1 }, atx { 1 }, cohesion{1}, separation{1}, alignment{1}{

}

void kmint::Redefined::update(float dt, std::vector<board_piece *> &_board_pieces) {
    auto vec = Linal::G2D::Vector(0, 0);

    if (attractedToAndreActive) vec += Linal::G2D::Vector(5, 5);
    if (attractedToAxelActive) vec += Linal::G2D::Vector(-5, -5);
    if (attractedToFransActive) vec += Linal::G2D::Vector(-5, 5);
    if (attractedToJohnnieActive) vec += Linal::G2D::Vector(5, -5);

    if (cohesionActive)
        vec += GetCohesionVec(_board_pieces) * cohesion;
    if (separationActive)
        vec += GetSeparationVec(_board_pieces) * separation;
    if (alignmentActive)
        vec += GetAlignmentVec(_board_pieces) * alignment;

    vec = vec.GetUnitVector();
    auto loc = location();

    auto newloc = kmint::point{ round(vec.x()) + loc.x(), round(vec.y()) + loc.y() };

    if (newloc.x() < 10) newloc.x(10); else if (newloc.x() > 1270) newloc.x(1270);
    if (newloc.y() < 10) newloc.y(10); else if (newloc.y() > 710) newloc.y(710);

    set_point(newloc);
}

/***********************
* CALCULATION OF STUFF *
***********************/
Linal::G2D::Vector Redefined::GetCohesionVec(std::vector< board_piece*> _board_pieces) {
    auto loc = location();
    auto vec = Linal::G2D::Vector(loc.x(), loc.y());

    int sumCount = 0;
    Linal::G2D::Vector vecSum;
    for (auto bp : _board_pieces)
    {
        if (auto bunny = dynamic_cast<kmint::Redefined*>(bp))
        {
            //if (bunny->hasDied()) continue;

            auto targetLoc = bp->location();
            if (targetLoc.x() == loc.x() && targetLoc.y() == loc.y())
                continue;

            auto targetVec = Linal::G2D::Vector(targetLoc.x(), targetLoc.y()) ;

            auto diff = (targetLoc - loc);
            if (std::abs(diff.x()) + std::abs(diff.y()) > 400)
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

Linal::G2D::Vector Redefined::GetSeparationVec(std::vector< board_piece*> _board_pieces) {
    auto loc = location();
    auto vec = Linal::G2D::Vector(loc.x(), loc.y());

    auto targetVecSum = Linal::G2D::Vector(0, 0);
    int count = 0;
    for (auto bp : _board_pieces)
    {
        if (auto bunny = dynamic_cast<kmint::Redefined*>(bp))
        {
            //if (bunny->hasDied()) continue;

            auto targetLoc = bp->location();
            if (loc.x() == targetLoc.x() && loc.y() == targetLoc.y())
                continue;

            auto targetVec = Linal::G2D::Vector(targetLoc.x(), targetLoc.y()) ;

            auto diffVec = targetVec - vec;

            if (std::abs(diffVec.x()) + std::abs(diffVec.y()) < 65)
            {
                targetVecSum = targetVecSum + targetVec;
                count++;
            }

        }
    }

    if (count > 0)
    {
        auto diffVec = (targetVecSum / count) - vec;
        return (vec - (targetVecSum / count)).GetUnitVector() * (65 - (std::abs(diffVec.x() + std::abs(diffVec.y()))));
    }


    return Linal::G2D::Vector(0, 0);
}

Linal::G2D::Vector Redefined::GetAlignmentVec(std::vector< board_piece*> _board_pieces) {
    auto loc = location();
    auto vec = Linal::G2D::Vector(loc.x(), loc.y());

    int sumCount = 0;
    Linal::G2D::Vector vecSum;
    for (auto bp : _board_pieces)
    {
        if (auto bunny = dynamic_cast<kmint::Redefined*>(bp))
        {
            //if (bunny->hasDied()) continue;

            auto targetLoc = bunny->location();
            if (targetLoc.x() == loc.x() && targetLoc.y() == loc.y())
                continue;

            auto diff = (targetLoc - loc);
            if (std::abs(diff.x()) + std::abs(diff.y()) > 150)
                continue;

            //vecSum = vecSum + bunny->GetVelocity();
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
double Redefined::getAttractionToAndre() const {
    return ata;
}

Redefined& Redefined::setAttractionToAndre(double ata) {
    this->ata = ata;
    return *this;
}

double Redefined::getAttractionToAxel() const {
    return atx;
}

Redefined& Redefined::setAttractionToAxel(double atx) {
    this->atx = atx;
    return *this;
}

double Redefined::getAttractionToFrans() const {
    return atf;
}

Redefined& Redefined::setAttractionToFrans(double atf) {
    this->atf = atf;
    return *this;
}

double Redefined::getAttractionToJohnnie() const {
    return atj;
}

Redefined& Redefined::setAttractionToJohnnie(double atj) {
    this->atj = atj;
    return *this;
}
