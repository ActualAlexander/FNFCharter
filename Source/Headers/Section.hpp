#ifndef SECTION_HPP
#define SECTION_HPP


#include <iostream>
#include <string>
#include <vector>


class Section {
    public:
        int sectionBeat;
        float startTime;
        float endTime;
        bool mustHitSection;
        bool changeBPM;
        int BPM;


        Section(int sectionBeat, bool mustHitSection, bool changeBPM, int BPM) : 
        sectionBeat(sectionBeat), mustHitSection(mustHitSection), changeBPM(changeBPM),
        BPM(BPM) {};


        void drawSection();


    private:
        bool isSectionActive = false;
        int noteNumber = 8;
        std::vector<Color> sectionColors = {WHITE, GRAY};
};

#endif