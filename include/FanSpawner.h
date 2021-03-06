//
// Created by administrator on 7-1-18.
//

#ifndef KMINTFRAMEWORK_BUNNYSPAWNER_H
#define KMINTFRAMEWORK_BUNNYSPAWNER_H

#include <algorithm>
#include <set>
#include <functional>
#include "Movable_objects/Fan/Fan.h"
#include "globals.hpp"
#include <list>

namespace kmint
{


    class FanSpawner
    {


    private:


        std::list<kmint::Fan*> currentFans;
        std::vector<kmint::board_piece*> _boardPieces;
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
                auto parrent1 = GetRandomParrent();
                auto parrent2 = GetRandomParrent();

                std::default_random_engine gen(rand() % 10000);
                std::uniform_int_distribution<int> pickAta(-1, 1), pickAtf(-1, 1), pickAtj(-1, 1), pickAtx(-1, 1), pickCoh(0, 1), pickSep(0, 1), pickAli(0, 1);

                std::uniform_int_distribution<int> xCord(10, 1270); // it's not a bug it's a feature: precision
                std::uniform_int_distribution<int> yCord(10, 690);

                // TO WORK OUT//
                std::vector<double> chromosomePool1 { 0, 0, 0, 0, 0, 0, 0 };//= { parrent1->getAttractionToAndre(), parrent1->getAttractionToFrans(), parrent1->getAttractionToJohnnie(), parrent1->getAttractionToAxel(), parrent1->getCohesion(), parrent1->getSeparation(), parrent1->getAlignment()};
                std::vector<double> chromosomePool2 { 0, 0, 0, 0, 0, 0, 0 };//= { parrent2->getAttractionToAndre(), parrent2->getAttractionToFrans(), parrent2->getAttractionToJohnnie(), parrent2->getAttractionToAxel(), parrent2->getCohesion(), parrent2->getSeparation(), parrent2->getAlignment()};

                std::vector<double> chromosomes {};

                // Just make sure no mistake is made
                if ( chromosomePool1.size() == chromosomePool2.size()) {
                    std::uniform_int_distribution<int> splitPoint(0, chromosomePool1.size() - 1);

                    bool splitStarted{false};

                    std::vector<double>::iterator it;


                    int index{0};
                    int splitPointIndex = splitPoint(gen);

                    for (it = chromosomePool1.begin(); it != chromosomePool1.end(); it++) {
                        if (splitPointIndex < index)
                            chromosomes.push_back(chromosomePool1[index]);
                        else
                            chromosomes.push_back(chromosomePool2[index]);

                        index++;
                    }
                }
                else
                {
                    // Code we should never reach but always make sure you have a backup plan
                    chromosomes.push_back(pickAta(gen) ? parrent1->getAttractionToAndre() : parrent2->getAttractionToAndre());
                    chromosomes.push_back(pickAtf(gen) ? parrent1->getAttractionToFrans() : parrent2->getAttractionToFrans());
                    chromosomes.push_back(pickAtj(gen) ? parrent1->getAttractionToJohnnie() : parrent2->getAttractionToJohnnie());
                    chromosomes.push_back(pickAtx(gen) ? parrent1->getAttractionToAxel() : parrent2->getAttractionToAxel());

                    chromosomes.push_back(pickCoh(gen) ? parrent1->getCohesion() : parrent2->getCohesion());
                    chromosomes.push_back(pickSep(gen) ? parrent1->getSeparation() : parrent2->getSeparation());
                    chromosomes.push_back(pickAli(gen) ? parrent1->getAlignment() : parrent2->getAlignment());
                }

                // END of new stuff //


                nextGen.push_back(new kmint::Fan{
                        kmint::point { xCord(gen), yCord(gen) },
                        kmint::image {"resources/xsfan.png", 1.0f},
                        chromosomes[0],
                        chromosomes[1],
                        chromosomes[2],
                        chromosomes[3],
                        chromosomes[4],
                        chromosomes[5],
                        chromosomes[6]
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

                for (auto bp : _boardPieces)
                    if (dynamic_cast<kmint::Fan*>(bp))
                        currentFans.push_back(dynamic_cast<kmint::Fan*>(bp));
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

//        bool sort_fan(const Fan* p1,const  Fan* p2) {
//            return p1->GetFitness() < p2->GetFitness() ||
//                   (p1->GetFitness() == p2->GetFitness());
//        }
        struct {
            bool operator()(const Fan* p1, const Fan* p2) {
                if(p1 != NULL && p2 != NULL){
                    return p1->fitness < p2->fitness ||
                           (p1->fitness == p2->fitness);
                }else{
                    false;
                }

            }
        } sort_fan;

        kmint::Fan* GetRandomParrent()
        {

            for (int i = 0; i < 1; i++)
            {
                std::default_random_engine gen(rand() % 10000);
            //TODO :: sort list



            currentFans.sort(sort_fan);

            std::list<Fan*> fans = currentFans;
            for(Fan* fan : fans){
                Fan* fan1 = fan;
            }
                int counter = 0;
                std::mt19937 rng;
                rng.seed(std::random_device()());
                std::uniform_int_distribution<std::mt19937::result_type> dist6(49,99);
                int number = dist6(rng);
                for(Fan* fan :currentFans){
                    if(counter  == number){
                        return fan;
                    }
                    counter++;
                }

//                auto it = currentFans.begin();
//                int count = 0;
//                for (auto b : currentFans) {
//                    if (b->GetFitness() > fitEnough(gen)) {
//                        return b;
//                        //auto copyBunny(b);
//                        //std::advance(it, count);
//                        //currentBunnies.erase(it);
//                        // TODO: Find a away to remove the bunny from the genPool after selection it as offspring. They dont have enough eggs and seeds for that!!
//                        //return copyBunny;
//                    }
//
//                    count++;
//                }
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