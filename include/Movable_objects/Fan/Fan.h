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
#include <Movable_objects/Sheep/Sheep.h>

namespace kmint {
    class Fan : public free_roaming_board_piece {
        image_drawable _drawable;
    public:
        Fan(point location, const image &i);

        const drawable &get_drawable() const override { return _drawable; }

        void update(float dt, std::vector< board_piece*> &_board_pieces);

        double getAttractionToAndre() const;
        double getAttractionToAxel() const;
        double getAttractionToFrans() const;
        double getAttractionToJohnnie() const;

        double getCohesion() const;
        double getSeparation() const;
        double getAlignment() const;

        Linal::G2D::Vector getVelocity() const;

        Fan& setAttractionToAndre(double);
        Fan& setAttractionToAxel(double);
        Fan& setAttractionToFrans(double);
        Fan& setAttractionToJohnnie(double);

        Fan& setCohesion(double);
        Fan& setSeparation(double);
        Fan& setAlignment(double);

        bool isAlive { true };
        const int GetFitness() const { return fitness; }
    private:
        void scanForNearbyFans(std::vector< board_piece*> &_board_pieces);

        std::vector<Linal::G2D::Vector> cohesionForces;
        std::vector<Linal::G2D::Vector> separationForces;
        std::vector<Linal::G2D::Vector> alignmentForces;

        Linal::G2D::Vector toAxel = {0, 0};
        Linal::G2D::Vector toAndre = {0, 0};
        Linal::G2D::Vector toFrans = {0, 0};
        Linal::G2D::Vector toJohnnie = {0, 0};

        Fan& setVelocity(Linal::G2D::Vector);

        Linal::G2D::Vector velocity { 0, 0 };

        double ata;
        double atf;
        double atj;
        double atx;

        double cohesion;
        double separation;
        double alignment;

        int fitness { 0 };
    };

    class Old : public free_roaming_board_piece {
        image_drawable _drawable;

    public:
        Old(point location, const image &i) : free_roaming_board_piece { location }, _drawable { *this,i } {
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

        Old(point location, const image &i, double ats, double atw, double coh, double sep, double ali)
            : free_roaming_board_piece { location }, _drawable { *this,i }, attractedToSheep(ats + 1), attractedToWater(atw + 1), cohesion(coh + 1), separation(sep + 1), alignment(ali + 1)
        {
            auto debug = false;
        }
        const drawable &get_drawable() const override { return _drawable; }

        const Linal::G2D::Vector& GetVelocity() { return velocity; }
        const int GetFitness() const { return fitness; }

        bool hasDied() { return isDead; }

        double GetAttractionToSheep(){ return attractedToSheep; }
        double GetAttractionToWater(){ return attractedToWater; }
        double GetCohesion() { return cohesion; }
        double GetSeparation() { return separation; }
        double GetAlignment() { return alignment; }

    private:
        Linal::G2D::Vector velocity { -10, 10 };
        double attractedToSheep;
        double attractedToWater;
        double cohesion;
        double separation;
        double alignment;

        int fitness = 0;
        bool isDead = false;


    public:
        bool isOnWater(std::vector< board_piece*> _board_pieces)
        {
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
            if (std::abs(diffVec.x()) + std::abs(diffVec.y()) <= 21) {
                return true;
            }

            return false;
        }
    };


}


#endif //KMINTFRAMEWORK_BUNNY_H
