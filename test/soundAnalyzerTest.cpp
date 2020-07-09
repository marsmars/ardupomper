//
// Created by PGD384 on 7/8/2020.
//

#include <Arduino.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include "soundAnalyzerTest.h"

using namespace testing;

class SoundAnalyzerTest : public Test {
protected:
    ArduinoMock& arduinoMock;
public:
    SoundAnalyzerTest() : arduinoMock {*arduinoMockInstance()} {}
};

TEST_F(SoundAnalyzerTest, GivenSoundAnalyzerWhenInitialiazedThenSilenceLevelIsSetUp){
    ASSERT_TRUE(soundAnalyzerSetup());
}