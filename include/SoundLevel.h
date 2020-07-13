//
// Created by PGD384 on 7/10/2020.
//

#ifndef ARDUPOMPER_SOUNDLEVEL_H
#define ARDUPOMPER_SOUNDLEVEL_H

#include "SoundSample.h"

enum class Sound {
    silence, failure, normal, unknown
};

const int levelNotSet = -1;
const int sampleSize = 10000;
const double precisionPercent = 10;

class SoundLevel {
private:
    int level = levelNotSet;
    SoundSample *sample;
    SoundLevel *nextLevel = 0;
    const Sound sound;
public:
    int getLevel() const;

    explicit SoundLevel(Sound sound) : sample{new SoundSample()}, nextLevel{0}, sound{sound} {}

    virtual ~SoundLevel() { delete sample; }

    int setLevel(int level);

    void setNextLevel(SoundLevel *nextLevel);

    Sound processInput(int input);

    bool isSampleProcessed() const;

    bool isLevelSet() const;

    bool isSampleAtLevel(int sample) const;

    void resetSampleIfAlreadyProcessed();

    Sound processNextLevel(int input) const;

    Sound setLevelIfSampleProcessed(int sampleLevel);

    Sound processAtLevel(int input, int sampleLevel) const;
};


#endif //ARDUPOMPER_SOUNDLEVEL_H
