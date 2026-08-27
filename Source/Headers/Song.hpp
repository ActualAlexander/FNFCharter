#ifndef SONG_HPP
#define SONG_HPP

#include <iostream>
#include <string>
#include <vector>

#include "raylib.h"

#include "Section.hpp"

class Song {
    public:
        std::string songName;
        std::string polishedSongName;
        std::string player1;
        std::string player2;
        std::string gf;
        std::string diffculty;
        std::vector<Section> sections;
        int BPM;
        int curBeat; // beat = 4 steps
        int curStep;
        float scrollSpeed;
        int stepPerBeat = 4;
        Music Inst;
        Music Voices;

        Song(
            std::string songName, 
            std::string diffculty
        ) : songName(songName), diffculty(diffculty) {};

        void loadSongAudio();
        void playSong();
        void stopSong();
        void calculateBeatsAndSteps(float deltaTime);
        void loadFromJson();
        void drawSection(int sectionNumber, float width);
        void manageSections();

    private:
        bool voicesCanPlay = false;
        bool instCanPlay = false;
        float beatTimer = 0.0f;
        float stepTimer = 0.0f;
        float minInSeconds = 60.0f;


};

#endif