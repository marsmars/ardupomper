//
// Created by PGD384 on 7/8/2020.
//

#include <gtest/gtest.h>
#include <tuple>
#include "SoundAnalyzer.h"

using testing::Test;
using testing::TestWithParam;
using testing::Values;
using std::tuple;
using std::make_tuple;

const int silenceLevel = 200;
const int failureLevel = 300;

class SoundAnalyzerTest : public TestWithParam<tuple<int, Sound>> {
protected:
    SoundAnalyzer *soundAnalyzer;

    virtual void SetUp() {
        soundAnalyzer = new SoundAnalyzer();
    }

    virtual void TearDown() {
        delete soundAnalyzer;
    }

    void initializeSoundLevel(SoundAnalyzer *soundAnalyzer, int silenceLevel) {
        for (int i = 0; i < sampleSize; i++) {
            soundAnalyzer->processInput(i % 2 ? silenceLevel - 1 : silenceLevel + 1);
        }
    }

    Sound processSample(SoundAnalyzer *soundAnalyzer, int inputLevel) {
        for (int i = 1; i < sampleSize; i++) {
            soundAnalyzer->processInput(i % 2 ? inputLevel - 1 : inputLevel + 1);
        }
        return soundAnalyzer->processInput(inputLevel);
    }
};

TEST_F(SoundAnalyzerTest, GivenSoundAnalyzerWhenSilenceSampleIsProcessedThenSilenceLevelIsSetButNotBefore) {
    for (int i = 0; i < sampleSize; i++) {
        ASSERT_FALSE(soundAnalyzer->isSilenceLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(i % 2 ? silenceLevel - 1 : silenceLevel + 1) == Sound::unknown);
    }
    ASSERT_TRUE(soundAnalyzer->isSilenceLevelSet());
}

TEST_F(SoundAnalyzerTest, GivenSilenceInitializedSoundAnalyzerWhenFailureSampleIsProcessedThenFailureLevelIsSetButNotBefore) {
    initializeSoundLevel(soundAnalyzer, silenceLevel);
    for (int i = 0; i < sampleSize; i++) {
        ASSERT_FALSE(soundAnalyzer->isFailureLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(i % 2 ? failureLevel - 1 : failureLevel + 1) == Sound::unknown);
    }
    ASSERT_TRUE(soundAnalyzer->isFailureLevelSet());
}

TEST_F(SoundAnalyzerTest, GivenSilenceInitializedSoundAnalyzerWhenProperSilenceSampleIsProcessedThenSilenceReturnedButNotBefore) {
    int inputLevel = 100;
    initializeSoundLevel(soundAnalyzer, inputLevel);
    for (int i = 1; i < sampleSize; i++) {
        ASSERT_TRUE(soundAnalyzer->isSilenceLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(i % 2 ? inputLevel - 1 : inputLevel + 1) == Sound::unknown);
    }
    ASSERT_TRUE(soundAnalyzer->processInput(101) == Sound::silence);
}

TEST_P(SoundAnalyzerTest, GivenInitializedSoundAnalyzerWhenSamplesAreProcessedThenCorrectSoundIsReturned) {
    SoundAnalyzer soundAnalyzer = SoundAnalyzer();
    int sample = std::get<0>(GetParam());
    Sound sound = std::get<1>(GetParam());
    initializeSoundLevel(&soundAnalyzer, silenceLevel);
    initializeSoundLevel(&soundAnalyzer, failureLevel);
    ASSERT_EQ(sound, processSample(&soundAnalyzer, sample));
}

INSTANTIATE_TEST_CASE_P(
        samplesProcessedTest,
        SoundAnalyzerTest,
        Values(
                make_tuple(silenceLevel, Sound::silence),
                make_tuple(failureLevel, Sound::failure),
                make_tuple(400, Sound::unknown)));