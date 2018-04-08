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
        Fan(point location, const image &i, double ata, double atf, double atj, double atx, double coh, double sep, double ali)
        : free_roaming_board_piece { location }, _drawable { *this,i }, ata(ata), atf(atf), atj(atj), atx(atx), cohesion(coh + 1), separation(sep + 1), alignment(ali + 1) {};
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
        int fitness { 0 };

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

    };
}


#endif //KMINTFRAMEWORK_BUNNY_H
