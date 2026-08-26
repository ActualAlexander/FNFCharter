#include <iostream>
#include <string>

#include "raylib.h"

#include "Section.hpp"


void Section::drawSection() {

    for (size_t i = 0; i < sectionBeat * 4; i++) {
        
        for (size_t j = 0; j < noteNumber; j++) {
            
            if (!(i % 2 == 0)) {
                DrawRectangle(50 * j, 50 *i, 50, 50, sectionColors.at(!(j%2==0)));
            } else {
                DrawRectangle(50 * j, 50 *i, 50, 50, sectionColors.at(j%2==0));
            }
        }
        
    }   
}