#include <iostream>
#include <string>

#include "raylib.h"

#include "Section.hpp"


void Section::drawSection() {
    
    size_t color_Index;
    
    bool isRowEven;

    for (size_t i = 0; i < sectionStep; i++) {
        isRowEven = i % 2 == 0;
        for (size_t j = 0; j < noteNumber; j++) {
            
            color_Index = j % 2 == 0;
            if (isRowEven) {
                DrawRectangle(50 * j, 50 *i, 50, 50, sectionColors.at(color_Index));
            } else {
                DrawRectangle(50 * j, 50 *i, 50, 50, sectionColors.at(!color_Index));
            }
        }
        
    }


    
}