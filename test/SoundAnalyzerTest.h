//
// Created by PGD384 on 7/12/2020.
//

#ifndef ARDUPOMPER_SOUNDANALYZERTEST_H
#define ARDUPOMPER_SOUNDANALYZERTEST_H
//
// Created by PGD384 on 7/8/2020.
//

#include <gtest/gtest.h>
#include <tuple>
#include "SoundAnalyzer.h"

using testing::TestWithParam;
using std::tuple;

const int baseLevel = 1000;
const int silenceLevel = 200;
const int failureLevel = 300;
const int normalLevel = 400;

int getVariableInput(int i, int level);

void initializeSoundLevel(SoundAnalyzer *soundAnalyzer, int soundLevel);

void initializeAnalyzer(SoundAnalyzer *soundAnalyzer);

Sound processSample(SoundAnalyzer *soundAnalyzer, int inputLevel);

#endif //ARDUPOMPER_SOUNDANALYZERTEST_H
