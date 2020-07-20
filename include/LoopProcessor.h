//
// Created by PGD384 on 7/20/2020.
//

#ifndef ARDUPOMPER_LOOPPROCESSOR_H
#define ARDUPOMPER_LOOPPROCESSOR_H


#include "Pomper.h"
#include "SoundAnalyzer.h"
#include "Leds.h"

class LoopProcessor {
    Pomper *pomper;
    SoundAnalyzer *analyzer;
    Leds *leds;

public:
    LoopProcessor(Pomper *pomper, SoundAnalyzer *analyzer, Leds *leds);

    virtual void stepPomperBack();

    virtual void processInput();

    virtual void changeLedsStates() const;

    virtual void printInitializedLevels() const;

    virtual void processSound(Sound sound);
};


#endif //ARDUPOMPER_LOOPPROCESSOR_H
