//
// Created by administrator on 21-12-17.
//

#include "a_star.h"
#include <climits>
#include <set>
#include <iostream>
#include<bits/stdc++.h>
#include <list>



namespace kmint {

    void a_star::search(graph *begin, node start, node end, bool debug) {
        //  std::vector<node> openList;      // Make it priority-able with the F score
        //open list priorty list on value
        // Creating & Initializing a map of String & Ints
        std::map<node, int> openList;




        // Declaring the type of Predicate that accepts 2 pairs and return a bool
        typedef std::function<bool(std::pair<node, int>, std::pair<node, int>)> Comparator;

        // Defining a lambda function to compare two pairs. It will compare two pairs using second field
        Comparator compFunctor =
                [](std::pair<node, int> elem1, std::pair<node, int> elem2) {
                    return elem1.second > elem2.second;
                };

        // Declaring a set that will store the pairs using above comparision logic
        std::set<std::pair<node, int>, Comparator> setOfWords(
                openList.begin(), openList.end(), compFunctor);

        // Iterate over a set using range base for loop
        // It will display the items in sorted order of values
        for (std::pair<node, int> element : setOfWords)
            std::cout << element.first.id() << " :: " << element.second << std::endl;
        // end of priorty list

        std::vector<node> closedList;

        //   openList.insert(std::pair<node, int>(start,0));

        node currentNode = start;

        /**
         * F Score = Score for square
         * G score = cost from start to square
         * H score = estimated cost from square
         *
         * H is calculated by pixel difference between the two points using the math.abs function
         * G is calculated by shortest path
         */
        for (edge edges: currentNode) {
            point location = edges.to().location();
            int h = std::abs(location.x() - end.location().x()) + std::abs(location.y() - end.location().y());
            int g = edges.weight();
            int f = h + g;

            openList.insert(std::pair<node, int>(edges.to(), f));
        }
        do {
            // @PSEUDO, get node with lowest heuristisk
            currentNode = openList.begin()->first;
            // @PSEUDO add this node to closedList
            closedList.push_back(currentNode);

            for (auto &j:*begin) {
                if (j.id() == currentNode.id()) {
                    j._color = color {0xff, 0xff, 0xff};

                }

            }
            //currentNode._color = color { 0xff, 0xff, 0x00 } ;
            // @PSEUDO remove this node from openList
            openList.erase(currentNode);

            if (currentNode.id() == end.id()) {
                return; // @TODO?? shouldn't this by a return, i never understood this
            }

            // std::vector connections = currentNode.getAllConnectedNodes();

            for (auto connection : currentNode) { // TODO replace openlist by connections

                // if connection is in closed list skip connection

                for (auto &closed: closedList) {
                    if (closed.id() == connection.to().id()) {
                        continue;
                    }
                }
                int result;

                for (auto open: openList) {
                    if (open.first.id() == connection.to().id()) {
                        result = open.second;

                    }
                }
                std::map<node,int>::iterator it;

                // if connection is in open list skip connection
                 it = openList.find(connection.to());
                if (it != openList.end()){
                    auto location = connection.to().location();
                int h = std::abs(location.x() - end.location().x()) +
                        std::abs(location.y() - end.location().y());
                int g = connection.weight();
                int f = h + g;
                if (result > f) {
                    result = f;
                }
                    continue;
            } else{
                    auto location = connection.to().location();
                    int h = std::abs(location.x() - end.location().x()) +
                            std::abs(location.y() - end.location().y());
                    int g = connection.weight();
                    int f = h + g;

                bool exist =false;
                    for(node& n : closedList){
                        if(n.id() == connection.to().id()){
                            exist =true;
                        }
                    }

                    if(exist == false){
                        openList.insert(std::pair<node, int>(connection.to(), f));

                    }


            }





            }
            openList.erase(currentNode);
            closedList.push_back(currentNode);
        } while (!openList.empty());

        // THERE IS NO PATH< OH HELP!
    }


    void a_star::search(graph *begin, node start, node end) {

    }
}
