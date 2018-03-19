//
// Created by administrator on 13-3-18.
//

#include "city.h"
namespace kmint {
    void city::fill(std::istream &is) {
        bool reading_nodes = true;
        int y = 0;
        for(std::string s; std::getline(is, s);) {
            if (s == "") {
                reading_nodes = false;
                continue;
            }else{
                int x = 0;
                for (auto c: s ){
                    point p{x,y};
                    if(c == 'B'){
                        _nodes.emplace_back(p,num_nodes(),color { 0x40,0x40,0x40 },0);
                    }
                    if(c == '1'){
                        _nodes.emplace_back(p,num_nodes(),color { 0xC0,0xC0,0xC0 },1);

                    }if(c == '2'){
                        _nodes.emplace_back(p,num_nodes(),color { 0xFF,0xFF,0x00 },2);

                    }if(c == '3'){
                        _nodes.emplace_back(p,num_nodes(),color { 0x80,0x00,0x00 },3);

                    }if(c == 'L'){
                        _nodes.emplace_back(p,num_nodes(),color { 0xFF,0x00,0x00 },0);

                    }if(c == 'N'){
                        _nodes.emplace_back(p,num_nodes(),color { 0x00,0xFF,0x00 },0);

                    }if(c == 'P'){
                        _nodes.emplace_back(p,num_nodes(),color {0x00,0x00,0xFF },0);

                    }if(c == 'C'){
                        _nodes.emplace_back(p,num_nodes(),color { 0xC0,0x00,0xFF },0);

                    }
                    x= x+20;

                }

            }
            y = y +20;

        }

    }
}
