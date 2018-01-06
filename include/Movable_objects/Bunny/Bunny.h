//
// Created by administrator on 21-12-17.
//

#ifndef KMINTFRAMEWORK_BUNNY_H
#define KMINTFRAMEWORK_BUNNY_H

#include <free_roaming_board_piece.h>
#include "graph_drawable.h"
#include <node.h>
#include <image_drawable.h>
#include <linal/vector.h>
#include <Movable_objects/Cow/Cow.h>
#include <random>

namespace kmint {

    class Bunny : public free_roaming_board_piece {
        image_drawable _drawable;

    public:
        Bunny(point location, const image &i) : free_roaming_board_piece { location }, _drawable { *this,i } {
            std::default_random_engine gen(rand() % 10000);
            std::uniform_int_distribution<int> sheep(-1000, 1000);
            std::uniform_int_distribution<int> water(-1000, 1000);
            std::uniform_int_distribution<int> cohes(0, 1000);
            std::uniform_int_distribution<int> separ(0, 1000);
            std::uniform_int_distribution<int> align(0, 1000);

            attractedToSheep = ((double) sheep(gen) / 1000) +1;
            attractedToWater = ((double) water(gen) / 1000) +1;
            cohesion         = ((double) cohes(gen) / 1000) +1;
            separation       = ((double) separ(gen) / 1000) +1;
            alignment        = ((double) align(gen) / 1000) +1;
        };
        const drawable &get_drawable() const override { return _drawable; }

        const Linal::G2D::Vector& GetVelocity() { return velocity; }

        void update(float dt, std::vector< board_piece*> &_board_pieces)
        {
            auto loc = location();

            auto sheep = GetAttractionToSheepVec(_board_pieces).GetUnitVector() * attractedToSheep;
            auto water = GetAttractionToWater(_board_pieces).GetUnitVector() * attractedToWater;
            auto cohes = GetCohesionVec(_board_pieces).GetUnitVector() * cohesion;
            auto separ = GetSeparationVec(_board_pieces) * separation;
            auto align = GetAlignmentVec(_board_pieces).GetUnitVector() * alignment;

            auto vec = (velocity + sheep + water + align + separ + cohes).GetUnitVector();

            auto newloc = kmint::point{ round(vec.x()) + loc.x(), round(vec.y()) + loc.y() };

            // No matter what, they can't get out of view
            if (newloc.x() < 10) newloc.x(10); else if (newloc.x() > 1270) newloc.x(1270);
            if (newloc.y() < 10) newloc.y(10); else if (newloc.y() > 690) newloc.y(690);

            set_point(newloc );

            velocity = vec;
        }

    private:
        Linal::G2D::Vector velocity { -10, 10 };
        double attractedToSheep;
        double attractedToWater;
        double cohesion;
        double separation;
        double alignment;

    public:
        Linal::G2D::Vector GetAttractionToSheepVec(std::vector< board_piece*> _board_pieces) {
            auto vec = Linal::G2D::Vector(location().x(), location().y());

            for (auto bp : _board_pieces)
            {
                if (dynamic_cast<kmint::Cow*>(bp))
                {
                    auto targetLoc = bp->location();
                    auto targetVec = Linal::G2D::Vector(targetLoc.x(), targetLoc.y());

                    return (targetVec - vec);
                }
            }

            return Linal::G2D::Vector(0, 0);
        }

        Linal::G2D::Vector GetAttractionToWater(std::vector< board_piece*> _board_pieces) {
            auto loc = location();
            auto vec = Linal::G2D::Vector(loc.x(), loc.y());

            int lowestDist = -1; // nan
            int lowestRow = 0;
            int lowestCol = 0;

            for (auto bp : _board_pieces)
            {
                if (dynamic_cast<kmint::graph*>(bp))
                {
                    auto graph = dynamic_cast<kmint::graph*>(bp);

                    unsigned int rowCount = 0;
                    unsigned int colCount = 0;

                    auto analyzes = graph->GetMapAnalysis();
                    for (auto row : analyzes)
                    {
                        colCount = 0;
                        for (bool isNode : row)
                        {
                            if (!isNode) { // then it's water
                                auto tarVec = Linal::G2D::Vector((colCount * 20) + 10, (rowCount * 20) + 10);
                                auto diffvec = tarVec - vec;
                                if (lowestDist < 0 || (std::abs(diffvec.x()) + std::abs(diffvec.y())) < lowestDist)
                                {
                                    lowestDist = std::abs(diffvec.x()) + std::abs(diffvec.y());
                                    lowestRow = rowCount;
                                    lowestCol = colCount;
                                }
                            }
                            colCount++;
                        }
                        rowCount++;
                    }
                    break;
                }
            }

            auto targetVec = Linal::G2D::Vector((lowestCol * 20) + 10, (lowestRow * 20) + 10);
            auto diffVec = targetVec - vec;
            if (std::abs(diffVec.x()) + std::abs(diffVec.y()) < 45) {
                return vec - targetVec;
            }

            return Linal::G2D::Vector(0, 0);
        }

        Linal::G2D::Vector GetCohesionVec(std::vector< board_piece*> _board_pieces) {
            auto loc = location();
            auto vec = Linal::G2D::Vector(loc.x(), loc.y());

            int sumCount = 0;
            Linal::G2D::Vector vecSum;
            for (auto bp : _board_pieces)
            {
                if (dynamic_cast<kmint::Bunny*>(bp))
                {
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

        Linal::G2D::Vector GetSeparationVec(std::vector< board_piece*> _board_pieces) {
            auto loc = location();
            auto vec = Linal::G2D::Vector(loc.x(), loc.y());

            auto targetVecSum = Linal::G2D::Vector(0, 0);
            int count = 0;
            for (auto bp : _board_pieces)
            {
                if (dynamic_cast<kmint::Bunny*>(bp))
                {
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
                return (vec - (targetVecSum / count)).GetUnitVector() * count;
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
                if (dynamic_cast<kmint::Bunny*>(bp))
                {
                    auto bunny = dynamic_cast<kmint::Bunny*>(bp);
                    bunny,GetVelocity();

                    auto targetLoc = bunny->location();
                    if (targetLoc.x() == loc.x() && targetLoc.y() == loc.y())
                        continue;

                    auto diff = (targetLoc - loc);
                    if (std::abs(diff.x()) + std::abs(diff.y()) > 150)
                        continue;

                    vecSum = vecSum + bunny->GetVelocity();
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
    };


}


#endif //KMINTFRAMEWORK_BUNNY_H
