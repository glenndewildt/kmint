//
// Created by administrator on 7-1-18.
//

#ifndef KMINTFRAMEWORK_BUNNYSPAWNER_H
#define KMINTFRAMEWORK_BUNNYSPAWNER_H

#include "Movable_objects/Fan/Fan.h"

namespace kmint
{
    class FanSpawner
    {

    private:
        std::vector<kmint::Fan*> currentBunnies;
        double ats = 0; // storaged average of attractionToSheep where fitness is equal or higher to fitness average
        double atw = 0; // storaged average of attractionToWater where fitness is equal or higher to fitness average
        double coh = 0; // storaged average of cohesion where fitness is equal or higher to fitness average
        double sep = 0; // storaged average of separation where fitness is equal or higher to fitness average
        double ali = 0; // storaged average of alignment where fitness is equal or higher to fitness average

        int maxFitness = 0;
        int minFitness = 0;
    public:
        FanSpawner(std::vector<kmint::board_piece*> _boardPieces) {
            for (auto bp : _boardPieces)
                if (dynamic_cast<kmint::Fan*>(bp))
                    currentBunnies.push_back(dynamic_cast<kmint::Fan*>(bp));
        }

        std::vector<kmint::Fan*> GetSpawnPool()
        {
            return GeneratePopulation();
        }

    private:
        std::vector<kmint::Fan*> GeneratePopulation()
        {
            std::vector<kmint::Fan*> nextGen;
            nextGen.clear();

            while (nextGen.size() < 20) {
                auto offSpring1 = GetRandomOffSpring();
                auto offSpring2 = GetRandomOffSpring();

                std::default_random_engine gen(rand() % 10000);
                std::uniform_int_distribution<int> pickAts(0, 1), pickAtw(0, 1), pickCoh(0, 1), pickSep(0, 1), pickAli(0, 1);

                std::uniform_int_distribution<int> xCord(10, 12700);
                std::uniform_int_distribution<int> yCord(10, 690);

                nextGen.push_back(new kmint::Fan{
                        kmint::point { xCord(gen), yCord(gen) },
                        kmint::image {"resources/fan.png", 0.33f},
                        pickAts(gen) ? offSpring1->GetAttractionToSheep() : offSpring2->GetAttractionToSheep(),
                        pickAtw(gen) ? offSpring1->GetAttractionToWater() : offSpring2->GetAttractionToWater(),
                        pickCoh(gen) ? offSpring1->GetCohesion() : offSpring2->GetCohesion(),
                        pickSep(gen) ? offSpring1->GetSeparation() : offSpring2->GetSeparation(),
                        pickAli(gen) ? offSpring1->GetAlignment() : offSpring2->GetAlignment()
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

                auto it = currentBunnies.begin();
                int count = 0;
                for (auto b : currentBunnies) {
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

            ats = 0;
            atw = 0;
            coh = 0;
            sep = 0;
            ali = 0;

            double countAnalyzable = currentBunnies.size();
            double selectedFitables = 0;

            for (auto b : currentBunnies) {
                if (b->GetFitness() < minFitness) minFitness = b->GetFitness();
                avgFitness += b->GetFitness();
                if (b->GetFitness() > maxFitness) maxFitness = b->GetFitness();
            }

            avgFitness = avgFitness / countAnalyzable;

            for (auto b : currentBunnies)
            {
                if (b->GetFitness() >= avgFitness) {
                    ats += b->GetAttractionToSheep();
                    atw += b->GetAttractionToWater();
                    coh += b->GetCohesion();
                    sep += b->GetSeparation();
                    ali += b->GetAlignment();

                    selectedFitables++;
                }
            }

            ats = ats / selectedFitables;
            atw = atw / selectedFitables;
            coh = coh / selectedFitables;
            sep = sep / selectedFitables;
            ali = ali / selectedFitables;
        }
    };
}

#endif //KMINTFRAMEWORK_BUNNYSPAWNER_H