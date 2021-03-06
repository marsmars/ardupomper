//
// Created by PGD384 on 7/11/2020.
//

#ifndef ARDUPOMPER_LEDS_H
#define ARDUPOMPER_LEDS_H

#include "SoundAnalyzer.h"

const int silenceLed = 3;
const int failureLed = 4;
const int normalLed = 5;

class Leds {
protected:
    SoundAnalyzer *analyzer;
public:

    Leds(SoundAnalyzer *analyzer);

    virtual void changeStates();

};


#endif //ARDUPOMPER_LEDS_H
