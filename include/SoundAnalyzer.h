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

    virtual Sound processInput(int input);

    virtual bool isSilenceLevelSet() const;

    virtual bool isFailureLevelSet() const;

    virtual bool isNormalLevelSet() const;

    virtual double getSilenceLevel() const;

    virtual double getFailureLevel() const;

    virtual double getNormalLevel() const;

    virtual bool isInitialized() const;
};


#endif //ARDUPOMPER_SOUNDANALYZER_H
