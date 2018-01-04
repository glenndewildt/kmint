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

            attractedToSheep = (double) sheep(gen) / 500;
            attractedToWater = (double) water(gen) / 500;
            cohesion         = (double) cohes(gen) / 500;
            separation       = (double) separ(gen) / 500;
            alignment        = (double)  align(gen) / 500;
        };
        const drawable &get_drawable() const override { return _drawable; }

        void update(float dt, std::vector< board_piece*> _board_pieces)
        {
            auto attSheep = GetAttractionToSheepVec(_board_pieces);

            attSheep = attSheep.GetUnitVector() * attractedToSheep;

            auto vec = attSheep;

            std::cout << "the attraction is " << attractedToSheep  << std::endl;

            set_point(kmint::point { vec.x() + location().x(), vec.y() + location().y() });
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

            return Linal::G2D::Vector(0, 0);
        }

        Linal::G2D::Vector GetCohesionVec(std::vector< board_piece*> _board_pieces) {
            auto vec = Linal::G2D::Vector(location().x(), location().y());

            return Linal::G2D::Vector(0, 0);
        }

        Linal::G2D::Vector GetSeparationVec(std::vector< board_piece*> _board_pieces) {
            auto vec = Linal::G2D::Vector(location().x(), location().y());

            for (auto bp : _board_pieces)
            {
                if (dynamic_cast<kmint::Bunny*>(bp))
                {
                    auto targetLoc = bp->location();
                    auto targetVec = Linal::G2D::Vector(targetLoc.x(), targetLoc.y());

                    auto diffVec = targetVec - vec;

                    if (diffVec.x() < 15)

                    if (attractedToSheep > 0) {
                        return (targetVec - vec).GetUnitVector();
                    }
                    else if (attractedToSheep < 0)
                    {
                        return (vec - targetVec).GetUnitVector();
                    }
                }
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
