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
    ArduinoMock& arduinoMock;
public:
    SoundAnalyzerTest() : arduinoMock {*arduinoMockInstance()} {}

    void initializeSilence(SoundAnalyzer& soundAnalyzer, int silenceLevel) {
        for (int i = 0; i < numberOfInitSamplesNeeded; i++) {
            ASSERT_FALSE(soundAnalyzer.isSilenceLevelSet());
            soundAnalyzer.processSample(i%2 ? silenceLevel - 1 : silenceLevel + 1);
        }
    }
};

TEST_F(SoundAnalyzerTest, GivenSoundAnalyzerWhenProcessedEnoughSilenceSamplesThenSilenceLevelIsSetButNotBefore){
    SoundAnalyzer soundAnalyzer;
    initializeSilence(soundAnalyzer, 1);
    ASSERT_TRUE(soundAnalyzer.isSilenceLevelSet());
}

TEST_F(SoundAnalyzerTest, GivenNonSilenceInitializedSoundAnalyzerWhenSilenceSampleProcessedThenUnknownReturned) {
    SoundAnalyzer soundAnalyzer;
    ASSERT_TRUE(soundAnalyzer.processSample(1) == Sound::unknown);
}

TEST_F(SoundAnalyzerTest, GivenSilenceInitializedSoundAnalyzerWhenSilenceSampleProcessedThenSilenceReturned) {
    SoundAnalyzer soundAnalyzer;
    initializeSilence(soundAnalyzer, 1);
    ASSERT_TRUE(soundAnalyzer.processSample(1) == Sound::silence);
}

TEST_F(SoundAnalyzerTest, GivenSilenceInitializedSoundAnalyzerWhenNonSilenceSampleProcessedThenUnknownReturned) {
    SoundAnalyzer soundAnalyzer;
    initializeSilence(soundAnalyzer, 5000);
    ASSERT_TRUE(soundAnalyzer.processSample(2) == Sound::unknown);
}


