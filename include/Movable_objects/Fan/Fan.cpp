//
// Created by administrator on 21-12-17.
//

#include <image.h>
#include <Movable_objects/Bandlit/bandlit.h>
#include "Fan.h"
#include "globals.hpp"

using namespace kmint;

Fan::Fan(point location, const image &i) : free_roaming_board_piece { location }, _drawable { *this,i}, ata { 1 }, atf { 1 }, atj { 1 }, atx { 1 }, cohesion{1}, separation{1}, alignment{1}{

}

void kmint::Fan::update(float dt, std::vector<board_piece *> &_board_pieces) {
    scanForNearbyFans(_board_pieces);

    Linal::G2D::Vector cohesionVec { Linal::G2D::Vector{ 0 , 0 }};
    Linal::G2D::Vector alignmentVec { Linal::G2D::Vector{ 0 , 0 }};
    Linal::G2D::Vector separationVec { Linal::G2D::Vector{ 0 , 0 }};

    for (auto coh : cohesionForces) {
        cohesionVec.x(cohesionVec.x() + coh.x());
        cohesionVec.y(cohesionVec.y() + coh.y());
    }

    for (auto sep : separationForces) {
        separationVec.x(separationVec.x() + sep.x());
        separationVec.y(separationVec.y() + sep.y());
    }

    for (auto ali : alignmentForces) {
        //alignmentVec.x(alignmentVec.x() + ali.x());
        //alignmentVec.y(alignmentVec.y() + ali.y());
    }

    //cohesionVec = cohesionVec.GetUnitVector() * cohesion;
    //alignmentVec = alignmentVec.GetUnitVector() * alignment;
    separationVec = separationVec.GetUnitVector() * separation;

    auto vec = (cohesionVec + alignmentVec + separationVec + toAxel.GetUnitVector() + toAndre.GetUnitVector() + toFrans.GetUnitVector() + toJohnnie.GetUnitVector()).GetUnitVector();
    auto loc = location();

    auto newloc = kmint::point{ round(vec.x()) + loc.x(), round(vec.y()) + loc.y() };

    if (newloc.x() < 10) newloc.x(10); else if (newloc.x() > 1270) newloc.x(1270);
    if (newloc.y() < 10) newloc.y(10); else if (newloc.y() > 710) newloc.y(710);

    set_point(newloc);

    setVelocity({ loc.x() - newloc.x(), loc.y() - newloc.y() });

    cohesionForces.clear();
    separationForces.clear();
    alignmentForces.clear();

    toAxel = {0, 0};
    toAndre = {0, 0};
    toFrans = {0, 0};
    toJohnnie = {0, 0};
}

/******************************
* SCANNING OF THE NEARBY AREA *
******************************/
void Fan::scanForNearbyFans(std::vector< board_piece*> &_board_pieces)
{
    auto fromLoc = location();

    for (auto bp : _board_pieces)
    {
        if (bp == this) continue; // Skip yourself

        if (auto fo = dynamic_cast<kmint::Fan*>(bp))
        {
            if (!fo->isAlive) continue; // Leave the dead alone

            auto tarLoc = fo->location();
            auto dist = getCoordDifference(tarLoc, fromLoc);

            if (cohesionActive && dist <= cohesionDistance) {
                cohesionForces.push_back({tarLoc.x() - fromLoc.x(), tarLoc.y() - fromLoc.y()});
            }

            if (separationActive && dist <= separationDistance) {
                separationForces.push_back({separationDistance - (tarLoc.x() - fromLoc.x()), separationDistance - ( tarLoc.y() - fromLoc.y())});
            }

            if (alignmentActive && dist <= alignmentDistance) {
                alignmentForces.push_back(fo->getVelocity());
            }
        }

        if (auto fo = dynamic_cast<kmint::bandlit*>(bp))
        {
            auto tarLoc = fo->location();
            auto dist = getCoordDifference(tarLoc, fromLoc);

            if (dist <= bandmemberDistance)
            {
                switch (fo->name) {
                    case kmint::bandlit::ANDRE:
                        if (attractedToAndreActive)
                            toAndre = {tarLoc.x() - fromLoc.x(), tarLoc.y() - fromLoc.y()};
                        break;
                    case kmint::bandlit::AXEL:
                        if (attractedToAxelActive)
                            toAxel = {tarLoc.x() - fromLoc.x(), tarLoc.y() - fromLoc.y()};
                        break;
                    case kmint::bandlit::FRANS:
                        if (attractedToFransActive)
                            toFrans = {tarLoc.x() - fromLoc.x(), tarLoc.y() - fromLoc.y()};
                        break;
                    case kmint::bandlit::JOHNNIE:
                        if (dist <= johnniedeadzone && heresjohnniemode)
                            isAlive = false;
                        else
                            if (attractedToJohnnieActive)
                                toJohnnie = {tarLoc.x() - fromLoc.x(), tarLoc.y() - fromLoc.y()};

                        break;
                }
            }

        }
    }
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