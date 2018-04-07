//
// Created by administrator on 7-4-18.
//

#include <Movable_objects/Bandlit/bandlit.h>
#include <Movable_objects/Manager/Manager.h>
#include "base_state.h"
#include "state_object.h"

#ifndef KMINTFRAMEWORK_WAIT_H
#define KMINTFRAMEWORK_WAIT_H
namespace kmint {
    class wait : public base_state {
    private:
        int bejaardenhuis= 25;
        int bibliotheek = 25;
        int cafe = 25;
        int poppoduim = 25;
        int counter;
        state_object *object;
    public:
        void OnExit() {
            std::cout << "Exit  wait state" << std::endl;


        };

        void OnEnter() {
            std::cout << "Enter  wait state" << std::endl;

        };

        wait(state_object *object) : counter{0}, object{object} {};
        int chose_job(){
            //make random number
            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(0,bejaardenhuis+bibliotheek+cafe+poppoduim);
            int number = dist6(rng);



            if(number >= 0 && number < bejaardenhuis){
                rng.seed(std::random_device()());
                std::uniform_int_distribution<std::mt19937::result_type> dist6(500,700);

                int sal = dist6(rng);
                if (dynamic_cast<kmint::bandlit *>(object)) {

                    kmint::bandlit *band = dynamic_cast<kmint::bandlit *>(object);
                    band->money = band->money + sal;
                }
                if(sal < 500){
                    if(bejaardenhuis > 5){
                        bejaardenhuis = bejaardenhuis -5;

                    }
                }else{
                    bejaardenhuis = bejaardenhuis +5;

                }
                return 120;
            }
            else if(number >= bejaardenhuis && number < bejaardenhuis+bibliotheek){
                rng.seed(std::random_device()());
                std::uniform_int_distribution<std::mt19937::result_type> dist6(200,300);

                int sal = dist6(rng);
                if (dynamic_cast<kmint::bandlit *>(object)) {

                    kmint::bandlit *band = dynamic_cast<kmint::bandlit *>(object);
                    band->money = band->money + sal;
                }
                if(sal < 500){
                    if(bibliotheek > 5){
                        bibliotheek = bibliotheek -5;
                    }
                }else{
                    bibliotheek = bibliotheek +5;

                }
                return 624;

            }
            else if(number >= bejaardenhuis+bejaardenhuis && number < bejaardenhuis+bibliotheek+cafe){
                rng.seed(std::random_device()());
                std::uniform_int_distribution<std::mt19937::result_type> dist6(500,500);

                int sal = dist6(rng);
                if (dynamic_cast<kmint::bandlit *>(object)) {

                    kmint::bandlit *band = dynamic_cast<kmint::bandlit *>(object);
                    band->money = band->money + sal;
                }
                if(sal < 500){
                    if(cafe > 5){
                        cafe = cafe -5;

                    }
                }else{
                    cafe = cafe +5;

                }
                return 1377;

            }
            else if(number >= bejaardenhuis+bejaardenhuis+cafe && number < bejaardenhuis+bibliotheek+cafe+poppoduim){
                rng.seed(std::random_device()());
                std::uniform_int_distribution<std::mt19937::result_type> dist6(300,1000);

                int sal = dist6(rng);
                if (dynamic_cast<kmint::bandlit *>(object)) {

                    kmint::bandlit *band = dynamic_cast<kmint::bandlit *>(object);
                    band->money = band->money + sal;
                }
                if(sal < 500){
                    if(poppoduim >5){
                        poppoduim = poppoduim -5;

                    }
                }else{

                    poppoduim = poppoduim +5;

                }
                return 573;

            }else{
                return 573;
            }


        }



        void check_state(std::vector<board_piece *> &_board_pieces, point my_location) {

            if (dynamic_cast<kmint::bandlit *>(object)) {

                kmint::bandlit *band = dynamic_cast<kmint::bandlit *>(object);
                for (auto bp : _board_pieces) {
                    if (dynamic_cast<Manager *>(bp)) {

                        kmint::Manager *man = dynamic_cast<kmint::Manager *>(bp);
                        if (man->get_node_id() == object->get_node_id()) {
                            std::cout << "manager is near appointment";
                            band->des_node_id = chose_job();
                            band->set_state("work");


                        }

                    }

                }
            }

        }


        void update() {
            std::cout << "wait state" << std::endl;
            object->set_node_id(520);
        };

        void draw() {};

    };
}


#endif //KMINTFRAMEWORK_WAIT_H
