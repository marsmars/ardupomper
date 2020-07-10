//
// Created by PGD384 on 7/9/2020.
//


#ifndef ARDUPOMPER_SOUNDANALYZER_H
#define ARDUPOMPER_SOUNDANALYZER_H

#include <memory>
#include "SoundLevel.h"

using namespace std;

enum class Sound {
    silence, failure, normal, unknown
};

class SoundAnalyzer {
private:
    unique_ptr<SoundLevel>  silence;
    unique_ptr<SoundLevel>  failure;
public:
    SoundAnalyzer(): silence{new SoundLevel()}, failure{new SoundLevel()}{};

    Sound processInput(int input);

    bool isSilenceLevelSet() const;
    bool isFailureLevelSet() const;
};


#endif //ARDUPOMPER_SOUNDANALYZER_H
