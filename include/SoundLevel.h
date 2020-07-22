//
// Created by PGD384 on 7/10/2020.
//

#ifndef ARDUPOMPER_SOUNDLEVEL_H
#define ARDUPOMPER_SOUNDLEVEL_H

#include "SoundSample.h"

enum class Sound {
    silence, failure, normal, unknown
};

const double levelNotSet = -1;
const double precisionPercent = 20;

class SoundLevel {
private:
    double level = levelNotSet;
    SoundSample *sample;
    SoundLevel *nextLevel = 0;
    const Sound sound;
public:
    double getLevel() const;

    explicit SoundLevel(Sound sound) : sample{new SoundSample()}, nextLevel{0}, sound{sound} {}

    virtual ~SoundLevel() { delete sample; }

    double setLevel(double level);

    void setNextSoundLevel(SoundLevel *nextLevel);

    Sound processInput(int input);

    Sound processSample(SoundSample *sample);

    bool isLevelSet() const;

    void resetSampleIfAlreadyProcessed();

    Sound processSampleAtNextLevel(SoundSample *sample);
};


#endif //ARDUPOMPER_SOUNDLEVEL_H
