#ifndef NOTE_HPP
#define NOTE_HPP

class Note {
    public:
        float timeWhenHit;
        int direction;
        float length;

        Note(float timeWhenHit, int direction, float length) : timeWhenHit(timeWhenHit), direction(direction), length(length) {};
};

#endif