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
            std::default_random_engine gen(rand());
            std::uniform_int_distribution<int> sheep(-1000, 1000);
            std::uniform_int_distribution<int> water(-1000, 1000);
            std::uniform_int_distribution<int> cohes(0, 1000);
            std::uniform_int_distribution<int> separ(0, 1000);
            std::uniform_int_distribution<int> align(0, 1000);

            attractedToSheep = (double) sheep(gen) / 1000;
            attractedToWater = (double) water(gen) / 1000;
            cohesion         = (double) cohes(gen) / 1000;
            separation       = 1; //(double) separ(gen) / 1000;
            alignment        = (double)  align(gen) / 1000;
        };
        const drawable &get_drawable() const override { return _drawable; }

        void update(float dt, std::vector< board_piece*> _board_pieces)
        {
            auto attSheep = GetAttractionToSheepVec(_board_pieces);
            auto attWater = GetAttractionToWater(_board_pieces);
            auto separ = GetSeparationVec(_board_pieces);

            //attSheep = attSheep.GetUnitVector() * attractedToSheep;

            auto vec = separ.GetUnitVector();

            auto newloc = kmint::point{ vec.x() + location().x(), vec.y() + location().y() };

            if (newloc.x() < 10) newloc.x(10); else if (newloc.x() > 1270) newloc.x(1270);
            if (newloc.y() < 10) newloc.y(10); else if (newloc.y() > 710) newloc.y(710);

            set_point(newloc );
        }

    private:
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
            auto vec = Linal::G2D::Vector(location().x(), location().y());


            int lowerX = vec.x() - 10;
            int upperX = vec.y() - 10;
            int lowerY = vec.x() + 10;
            int upperY = vec.y() + 10;

            for (auto bp : _board_pieces)
            {
                if (dynamic_cast<kmint::graph*>(bp))
                {
                    auto graph = dynamic_cast<kmint::graph*>(bp);
                    for(auto node : *graph)
                    {
                        if (
                                (unsigned int) (node.location().x() - lowerX) <= (upperX - lowerX)  &&
                                (unsigned int) (node.location().y() - lowerY) <= (upperY - lowerY))
                        {
                            // It's a node
                            return Linal::G2D::Vector(200, 200);
                        }
                        else
                        {
                        }
                    }
                }
            }


            return Linal::G2D::Vector(0, 0);
        }

        Linal::G2D::Vector GetCohesionVec(std::vector< board_piece*> _board_pieces) {
            auto vec = Linal::G2D::Vector(location().x(), location().y());

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

                    if (std::abs(diffVec.x()) + std::abs(diffVec.y()) < 45)
                    {
                        targetVecSum = targetVecSum + targetVec;
                        count++;
                    }

                }
            }

            if (count > 0)
            {
                return (vec - (targetVecSum / count));
            }


            return Linal::G2D::Vector(0, 0);
        }

        Linal::G2D::Vector GetAlignmentVec(std::vector< board_piece*> _board_pieces) {
            auto vec = Linal::G2D::Vector(location().x(), location().y());

            return Linal::G2D::Vector(0, 0);
        }
    };


}


#endif //KMINTFRAMEWORK_BUNNY_H
