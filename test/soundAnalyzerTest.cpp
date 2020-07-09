//
// Created by PGD384 on 7/8/2020.
//

#include <Arduino.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include "soundAnalyzer.h"

using namespace testing;

class SoundAnalyzerTest : public Test {
protected:
    ArduinoMock &arduinoMock;
    SoundAnalyzer *soundAnalyzer;
protected:
    virtual void SetUp() {
        soundAnalyzer = new SoundAnalyzer();
    }

    virtual void TearDown() {
        delete soundAnalyzer;
    }

    void initializeSilence(int silenceLevel) {
        for (int i = 0; i < silenceInitSampleSize; i++) {
            ASSERT_FALSE(soundAnalyzer->isSilenceLevelSet());
            ASSERT_TRUE(soundAnalyzer->processInput(i % 2 ? silenceLevel - 1 : silenceLevel + 1) == Sound::unknown);
        }
    }

    void processSample(int inputLevel) {
        for (int i = 1; i < sampleSize; i++) {
            ASSERT_TRUE(soundAnalyzer->processInput(i % 2 ? inputLevel - 1 : inputLevel + 1) == Sound::unknown);
        }
    }

public:
    SoundAnalyzerTest() : arduinoMock{*arduinoMockInstance()} {}

};

TEST_F(SoundAnalyzerTest, GivenSoundAnalyzerWhenProcessedEnoughSilenceSamplesThenSilenceLevelIsSetButNotBefore) {
    initializeSilence(1);
    ASSERT_TRUE(soundAnalyzer->isSilenceLevelSet());
}

TEST_F(SoundAnalyzerTest, GivenSilenceInitializedSoundAnalyzerWhenProperSilenceSampleIsProcessedThenSilenceReturned) {
    initializeSilence(100);
    processSample(100);
    ASSERT_TRUE(soundAnalyzer->processInput(101) == Sound::silence);
}

TEST_F(SoundAnalyzerTest, GivenSilenceInitializedSoundAnalyzerWhenNonSilenceSampleProcessedThenUnknownReturned) {
    initializeSilence(5000);
    ASSERT_TRUE(soundAnalyzer->processInput(2) == Sound::unknown);
}



