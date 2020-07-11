//
// Created by PGD384 on 7/9/2020.
//


#ifndef ARDUPOMPER_SOUNDANALYZER_H
#define ARDUPOMPER_SOUNDANALYZER_H

#include <memory>
#include "SoundLevel.h"

using std::shared_ptr;

class SoundAnalyzer {
private:
    shared_ptr<SoundLevel>  silence;
    shared_ptr<SoundLevel>  failure;
public:
    SoundAnalyzer();

    Sound processInput(int input);

    bool isSilenceLevelSet() const;
    bool isFailureLevelSet() const;
};


#endif //ARDUPOMPER_SOUNDANALYZER_H
