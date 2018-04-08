//
// Created by administrator on 7-1-18.
//

#ifndef KMINTFRAMEWORK_BUNNYSPAWNER_H
#define KMINTFRAMEWORK_BUNNYSPAWNER_H

#include "Movable_objects/Fan/Fan.h"
#include "globals.hpp"

namespace kmint
{
    class FanSpawner
    {

    private:
        std::vector<kmint::Fan*> currentFans;
        double ata = 0; // storaged average of attraction to bandlid where fitness is equal or higher to fitness average
        double atf = 0; // storaged average of attraction to bandlid where fitness is equal or higher to fitness average
        double atj = 0; // storaged average of attraction to bandlid where fitness is equal or higher to fitness average
        double atx = 0; // storaged average of attraction to bandlid where fitness is equal or higher to fitness average

        double coh = 0; // storaged average of cohesion where fitness is equal or higher to fitness average
        double sep = 0; // storaged average of separation where fitness is equal or higher to fitness average
        double ali = 0; // storaged average of alignment where fitness is equal or higher to fitness average



        int maxFitness = 0;
        int minFitness = 0;
    public:
        FanSpawner(std::vector<kmint::board_piece*> _boardPieces) {
            for (auto bp : _boardPieces)
                if (dynamic_cast<kmint::Fan*>(bp))
                    currentFans.push_back(dynamic_cast<kmint::Fan*>(bp));
        }

        std::vector<kmint::Fan*> GetSpawnPool()
        {
            decideChromesomeValue();
            selectOffspring();

            return GeneratePopulation();
        }

    private:
        void decideChromesomeValue() {
            for (auto fan : currentFans) {
                ata += fan->getAttractionToAndre() * fan->GetFitness();
                atf += fan->getAttractionToFrans() * fan->GetFitness();
                atj += fan->getAttractionToJohnnie() * fan->GetFitness();
                atx += fan->getAttractionToAxel() * fan->GetFitness();

                coh += fan->getCohesion() * fan->GetFitness();
                sep += fan->getSeparation() * fan->GetFitness();
                ali += fan->getAlignment() * fan->GetFitness();
            }

            bool breakpoint = true;
        };

        void selectParent() {

        };

        void selectOffspring() {}; // Which parent does deliver the chromesome of type X

        std::vector<kmint::Fan*> GeneratePopulation()
        {
            std::vector<kmint::Fan*> nextGen;
            nextGen.clear();

            while (nextGen.size() < fansToSpawn) {
                auto offSpring1 = GetRandomOffSpring();
                auto offSpring2 = GetRandomOffSpring();

                std::default_random_engine gen(rand() % 10000);
                std::uniform_int_distribution<int> pickAta(-1, 1), pickAtf(-1, 1), pickAtj(-1, 1), pickAtx(-1, 1), pickCoh(0, 1), pickSep(0, 1), pickAli(0, 1);

                std::uniform_int_distribution<int> xCord(10, 12700); // it's not a bug it's a feature: precision
                std::uniform_int_distribution<int> yCord(10, 690);

                nextGen.push_back(new kmint::Fan{
                        kmint::point { xCord(gen), yCord(gen) },
                        kmint::image {"resources/xsfan.png", 1.0f},
                        pickAta(gen) ? offSpring1->getAttractionToAndre() : offSpring2->getAttractionToAndre(),
                        pickAtf(gen) ? offSpring1->getAttractionToFrans() : offSpring2->getAttractionToFrans(),
                        pickAtj(gen) ? offSpring1->getAttractionToJohnnie() : offSpring2->getAttractionToJohnnie(),
                        pickAtx(gen) ? offSpring1->getAttractionToAxel() : offSpring2->getAttractionToAxel(),
                        pickCoh(gen) ? offSpring1->getCohesion() : offSpring2->getCohesion(),
                        pickSep(gen) ? offSpring1->getSeparation() : offSpring2->getSeparation(),
                        pickAli(gen) ? offSpring1->getAlignment() : offSpring2->getAlignment()
                });
            }

            return nextGen;
        }

        /**
         * @Todo if this doesnt work remove the erase
         */
        kmint::Fan* GetRandomOffSpring()
        {

            for (int i = 0; i < 1; i++)
            {
                std::default_random_engine gen(rand() % 10000);
                std::uniform_int_distribution<int> fitEnough(minFitness, maxFitness);

                auto it = currentFans.begin();
                int count = 0;
                for (auto b : currentFans) {
                    if (b->GetFitness() > fitEnough(gen)) {
                        return b;
                        //auto copyBunny(b);
                        //std::advance(it, count);
                        //currentBunnies.erase(it);
                        // TODO: Find a away to remove the bunny from the genPool after selection it as offspring. They dont have enough eggs and seeds for that!!
                        //return copyBunny;
                    }

                    count++;
                }
            }

        }

        /**
         * Find logic within fitness value and the individual settings
         */
        void AnalizeFitness()
        {
            double avgFitness = 0;

            ata = 0;
            atf = 0;
            atj = 0;
            atx = 0;

            coh = 0;
            sep = 0;
            ali = 0;

            double countAnalyzable = currentFans.size();
            double selectedFitables = 0;

            for (auto b : currentFans) {
                if (b->GetFitness() < minFitness) minFitness = b->GetFitness();
                avgFitness += b->GetFitness();
                if (b->GetFitness() > maxFitness) maxFitness = b->GetFitness();
            }

            avgFitness = avgFitness / countAnalyzable;

            for (auto b : currentFans)
            {
                if (b->GetFitness() >= avgFitness) {
                    //coh += b->GetCohesion();
                    //sep += b->GetSeparation();
                    //ali += b->GetAlignment();

                    selectedFitables++;
                }
            }

            ata = ata / selectedFitables;
            atf = atf / selectedFitables;
            coh = coh / selectedFitables;
            sep = sep / selectedFitables;
            ali = ali / selectedFitables;
        }
    };
}

#endif //KMINTFRAMEWORK_BUNNYSPAWNER_H