//
// Created by PGD384 on 7/9/2020.
//


#ifndef ARDUPOMPER_SOUNDANALYZER_H
#define ARDUPOMPER_SOUNDANALYZER_H

#include "SoundLevel.h"

class SoundAnalyzer {
private:
    SoundLevel *silence;
    SoundLevel *failure;
    SoundLevel *normal;
public:
    SoundAnalyzer();

    virtual ~SoundAnalyzer();

    Sound processInput(int input);

    bool isSilenceLevelSet() const;

    bool isFailureLevelSet() const;

    bool isNormalLevelSet() const;

    double getSilenceLevel() const;

    double getFailureLevel() const;

    double getNormalLevel() const;

    bool isInitialized();
};


#endif //ARDUPOMPER_SOUNDANALYZER_H
