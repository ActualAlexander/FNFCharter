#ifndef SECTION_HPP
#define SECTION_HPP


#include <iostream>
#include <string>
#include <vector>


class Section {
    public:
        int sectionBeat;
        int sectionStep = sectionBeat * 4;
        int noteNumber = 8;
        int BPM;
        float startTime;
        float endTime;
        bool mustHitSection;
        bool changeBPM;
        bool isSectionActive = false;
        std::vector<Color> sectionColors = {WHITE, GRAY};
        

        Section(int sectionBeat, bool mustHitSection, bool changeBPM, int BPM) : 
        sectionBeat(sectionBeat), mustHitSection(mustHitSection), changeBPM(changeBPM),
        BPM(BPM) {};


        void drawSection();


    private:

        
};

#endif