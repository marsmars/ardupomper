//
// Created by PGD384 on 7/17/2020.
//

#ifndef ARDUPOMPER_MAIN_H
#define ARDUPOMPER_MAIN_H

#include "SoundAnalyzer.h"
#include "Button.h"
#include "Pomper.h"
#include "Leds.h"
#include "LoopProcessor.h"

const int baudRate = 9600;

void mainLoop(LoopProcessor *loopProcessor, Button *button, Pomper *pomper, SoundAnalyzer *analyzer, Leds *leds);

void setupMain();

#endif //ARDUPOMPER_MAIN_H
