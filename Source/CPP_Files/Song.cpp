#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "raylib.h"

#include "Song.hpp"

using json = nlohmann::json;

void Song::loadSongAudio() {
    const std::string voicesPath = "Data/" + songName + "/Voices.ogg";
    const std::string instPath = "Data/" + songName + "/Inst.ogg";

    //--------------- Voice.ogg ------------------
    if (FileExists(voicesPath.c_str())) {
        std::cout << songName + "Voices.ogg was found" << std::endl;
        voicesCanPlay = true;
        Voices = LoadMusicStream(voicesPath.c_str());

    } else {
        std::cout << songName + "Voices.ogg wasn't found" << std::endl;
        voicesCanPlay = false;
    }


    //--------------- Inst.ogg ------------------

    if (FileExists(instPath.c_str())) {
        std::cout << songName + "Inst.ogg was found" << std::endl;
        instCanPlay = true;
        Inst = LoadMusicStream(instPath.c_str());

    } else {
        std::cout << songName + "Inst.ogg wasn't found" << std::endl;
        instCanPlay = false;
    }

}


void Song::playSong() {
    if(voicesCanPlay) {
        PlayMusicStream(Voices);
    }
    if (instCanPlay) {
        PlayMusicStream(Inst);
    }
}

void Song::stopSong() {
    if(voicesCanPlay) {
        PauseMusicStream(Voices);
    }
    if (instCanPlay) {
        PauseMusicStream(Inst);
    }
}

void Song::calculateBeatsAndSteps(float deltaTime) {
    beatTimer += deltaTime;
    stepTimer += deltaTime;

    float secondsPerBeat = minInSeconds/BPM;
    //  I Step = 1/4 Beats -> 1 secondsPerStep = 1/4 secondsPerBeat
    float secondsPerStep = secondsPerBeat / 4;
    
    if (beatTimer >= secondsPerBeat) {
        curBeat ++;
        beatTimer -= secondsPerBeat;
    }

    if (stepTimer >= secondsPerStep) {
        curStep ++;
        stepTimer -= secondsPerStep;
    }

}


void Song::loadFromJson() {
    const std::string jsonPath = "Data/" + songName + "/data/" + diffculty + ".json";
    if (FileExists(jsonPath.c_str())) {
        std::cout << songName + "-" + diffculty + ".json was found";
        std::ifstream jsonFile(jsonPath);
        
        json charts;
        jsonFile >> charts;

        polishedSongName = charts["song"]["song"];
        player1 = charts["song"]["player1"];
        player2 = charts["song"]["player2"];
        gf = charts["song"]["gfVersion"];
        scrollSpeed = charts["song"]["speed"];
        BPM = charts["song"]["bpm"];
        for (size_t i = 0; i < charts["song"]["notes"].size(); i++) {
            
            auto &section = charts["song"]["notes"][i];

            sections.push_back(
                Section(
                    section["sectionBeats"], section["mustHitSection"], 
                    section["changeBPM"], section["bpm"]
                )
            );

        }
        
        

    } else {
        std::cout << songName + "-" + diffculty + ".json wasn't found";
    }
}


void Song::drawSection(int sectionNumber, float width) {
    
    size_t color_Index;
    
    Vector2 sectionPosition = {0, 0};

    bool isRowEven;
    bool isSectionEven = sectionNumber % 2 == 0;
    float totalSectionWidth = width * (sections.at(sectionNumber).sectionStep - 1);
    float yPositionBuffer = totalSectionWidth * sectionNumber;

    
    for (size_t i = 0; i < sections.at(sectionNumber).sectionStep; i++) {
        isRowEven = i % 2 == 0;
        for (size_t j = 0; j < sections.at(sectionNumber).noteNumber; j++) {
            
            color_Index = j % 2 == 0;
            sectionPosition.x = width * j;
            sectionPosition.y = width * i + yPositionBuffer;
            DrawRectangle(
                sectionPosition.x, sectionPosition.y, 
                width, width, 
                sections.at(sectionNumber).sectionColors.at(
                    isSectionEven ?
                        isRowEven ?
                        color_Index:
                        !color_Index :
                        isRowEven?
                        !color_Index:
                        color_Index
                )
            );
        }
        
    }
}

void Song::manageSections() {
    for(size_t i = 0; i < sections.size(); i++ ) {
        // if (curBeat >= sections.at(i).sectionBeat * (i)) {
        //     sections.at(i).isSectionActive = false;
        // } else {
        //     sections.at(i).isSectionActive = true;
        // }
        if (sections.at(i).isSectionActive) {
            sections.at(i).sectionColors = {WHITE, GRAY};
        }

        if (!sections.at(i).isSectionActive) {
            sections.at(i).sectionColors = {DARKGRAY, GRAY};
        }

        if (curStep <= sections.at(i).sectionStep * (i + 1) && curStep >= sections.at(i).sectionStep * i) {
            sections.at(i).isSectionActive = true;
        } else {
            sections.at(i).isSectionActive = false;
        }

        

        if(i < 10 ) std::cout << "Section " + std::to_string(i) + " is " + std::to_string(sections.at(i).isSectionActive) << std::endl;  

        if(i < 10) drawSection(i, 50);
    }
}

