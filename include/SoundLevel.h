//
// Created by PGD384 on 7/10/2020.
//

#ifndef ARDUPOMPER_SOUNDLEVEL_H
#define ARDUPOMPER_SOUNDLEVEL_H

#include <memory>
#include "SoundSample.h"

using std::unique_ptr;
using std::shared_ptr;

enum class Sound {
    silence, failure, normal, unknown
};

const int levelNotSet = -1;
const int sampleSize = 500;
const double precisionPercent = 10;

class SoundLevel {
private:
    int level = levelNotSet;
    unique_ptr<SoundSample> sample;
    shared_ptr<SoundLevel> nextLevel;
    const Sound sound;
public:
    explicit SoundLevel(Sound sound) : sound{sound}, sample{new SoundSample()} {}

    int setLevel(int level);

    void setNextLevel(shared_ptr<SoundLevel> nextLevel);

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
