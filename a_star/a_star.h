//
// Created by administrator on 21-12-17.
//

#ifndef KMINTFRAMEWORK_A_STAR_H
#define KMINTFRAMEWORK_A_STAR_H

#include <graph.h>
#include "node.h"

namespace kmint {
  using  namespace std;

    class a_star {

public:
    a_star() {};

    void search( graph*, node, node);
    std::vector<node> search( graph*, node, node, bool);

};

}

#endif //KMINTFRAMEWORK_A_STAR_H
