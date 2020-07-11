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
const int normalLevel = 400;

class SoundAnalyzerTest : public TestWithParam<tuple<int, Sound>> {
protected:
    SoundAnalyzer *soundAnalyzer;

    virtual void SetUp() {
        soundAnalyzer = new SoundAnalyzer();
    }

    virtual void TearDown() {
        delete soundAnalyzer;
    }

    void initializeSoundLevel(SoundAnalyzer *soundAnalyzer, int soundLevel) {
        for (int i = 0; i < sampleSize; i++) {
            soundAnalyzer->processInput(i % 2 ? soundLevel - 1 : soundLevel + 1);
        }
    }

    void initializeAnalyzer(SoundAnalyzer *soundAnalyzer) {
        initializeSoundLevel(soundAnalyzer, silenceLevel);
        initializeSoundLevel(soundAnalyzer, failureLevel);
        initializeSoundLevel(soundAnalyzer, normalLevel);
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

TEST_F(SoundAnalyzerTest,
       GivenSilenceInitializedSoundAnalyzerWhenFailureSampleIsProcessedThenFailureLevelIsSetButNotBefore) {
    initializeSoundLevel(soundAnalyzer, silenceLevel);
    for (int i = 0; i < sampleSize; i++) {
        ASSERT_FALSE(soundAnalyzer->isFailureLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(i % 2 ? failureLevel - 1 : failureLevel + 1) == Sound::unknown);
    }
    ASSERT_TRUE(soundAnalyzer->isFailureLevelSet());
}

TEST_F(SoundAnalyzerTest,
       GivenSilenceInitializedSoundAnalyzerWhenProperSilenceSampleIsProcessedThenSilenceReturnedButNotBefore) {
    int inputLevel = 100;
    initializeSoundLevel(soundAnalyzer, inputLevel);
    for (int i = 1; i < sampleSize; i++) {
        ASSERT_TRUE(soundAnalyzer->isSilenceLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(i % 2 ? inputLevel - 1 : inputLevel + 1) == Sound::unknown);
    }
    ASSERT_TRUE(soundAnalyzer->processInput(101) == Sound::silence);
}

INSTANTIATE_TEST_CASE_P(
        samplesProcessedTest,
        SoundAnalyzerTest,
        Values(
                make_tuple(silenceLevel, Sound::silence),
                make_tuple(failureLevel, Sound::failure),
                make_tuple(normalLevel, Sound::normal),
                make_tuple(silenceLevel+20, Sound::silence),
                make_tuple(failureLevel-30, Sound::failure),
                make_tuple(normalLevel+40, Sound::normal),
                make_tuple(silenceLevel-21, Sound::unknown),
                make_tuple(failureLevel+31, Sound::unknown),
                make_tuple(normalLevel-41, Sound::unknown),
                make_tuple(500, Sound::unknown),
                make_tuple(5000, Sound::unknown),
                make_tuple(50000, Sound::unknown)));

TEST_P(SoundAnalyzerTest, GivenInitializedSoundAnalyzerWhenSamplesAreProcessedThenCorrectSoundIsReturned) {
    SoundAnalyzer soundAnalyzer = SoundAnalyzer();
    initializeAnalyzer(&soundAnalyzer);
    int sample = std::get<0>(GetParam());
    Sound sound = std::get<1>(GetParam());
    ASSERT_EQ(sound, processSample(&soundAnalyzer, sample));
}
