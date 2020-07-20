//
// Created by PGD384 on 7/8/2020.
//

#include "SoundAnalyzerTest.h"
#include "SoundAnalyzer.h"

using testing::Test;
using testing::TestWithParam;
using testing::Values;
using std::tuple;
using std::make_tuple;

int getVariableInput(int i, int level) {
    return i % 2 ? baseLevel - level: baseLevel + level;
}

void initializeSoundLevel(SoundAnalyzer *soundAnalyzer, int soundLevel) {
    for (int i = 0; i < sampleSize; i++) {
        soundAnalyzer->processInput(getVariableInput(i, soundLevel));
    }
}

void initializeAnalyzer(SoundAnalyzer *soundAnalyzer) {
    initializeSoundLevel(soundAnalyzer, silenceLevel);
    initializeSoundLevel(soundAnalyzer, failureLevel);
    initializeSoundLevel(soundAnalyzer, normalLevel);
}

Sound processSample(SoundAnalyzer *soundAnalyzer, int inputLevel) {
    for (int i = 1; i < sampleSize; i++) {
        soundAnalyzer->processInput(getVariableInput(i, inputLevel));
    }
    return soundAnalyzer->processInput(baseLevel + inputLevel);
}

class SoundAnalyzerTest : public TestWithParam<tuple<int, Sound>> {
protected:
    SoundAnalyzer *soundAnalyzer;

    virtual void SetUp();

    virtual void TearDown();
};

void SoundAnalyzerTest::SetUp() {
    Test::SetUp();
    soundAnalyzer = new SoundAnalyzer();
}

void SoundAnalyzerTest::TearDown() {
    Test::TearDown();
    delete soundAnalyzer;
}

TEST_F(SoundAnalyzerTest, GivenSoundAnalyzerWhenSilenceSampleIsProcessedThenSilenceLevelIsSetButNotBefore) {
    for (int i = 0; i < sampleSize; i++) {
        ASSERT_FALSE(soundAnalyzer->isSilenceLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(getVariableInput(i, silenceLevel)) == Sound::unknown);
    }
    ASSERT_TRUE(soundAnalyzer->isSilenceLevelSet());
}

TEST_F(SoundAnalyzerTest,
       GivenSilenceInitializedSoundAnalyzerWhenFailureSampleIsProcessedThenFailureLevelIsSetButNotBefore) {
    initializeSoundLevel(soundAnalyzer, silenceLevel);
    for (int i = 0; i < sampleSize; i++) {
        ASSERT_FALSE(soundAnalyzer->isFailureLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(getVariableInput(i, failureLevel)) == Sound::unknown);
    }
    ASSERT_TRUE(soundAnalyzer->isFailureLevelSet());
}

TEST_F(SoundAnalyzerTest,
       GivenSilenceAndFailureInitializedSoundAnalyzerWhenNormalSampleIsProcessedThenNormalLevelIsSetButNotBefore){
    initializeSoundLevel(soundAnalyzer, silenceLevel);
    initializeSoundLevel(soundAnalyzer, failureLevel);
    for (int i = 0; i < sampleSize; i++) {
        ASSERT_FALSE(soundAnalyzer->isNormalLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(getVariableInput(i, normalLevel)) == Sound::unknown);
    }
    ASSERT_TRUE(soundAnalyzer->isNormalLevelSet());
}

TEST_F(SoundAnalyzerTest,
       GivenSilenceInitializedSoundAnalyzerWhenSilenceInitilizedAgainThenNoOtherLevelIsInitialized) {
    initializeSoundLevel(soundAnalyzer, silenceLevel);
    initializeSoundLevel(soundAnalyzer, silenceLevel);
    ASSERT_FALSE(soundAnalyzer->isFailureLevelSet());
    ASSERT_FALSE(soundAnalyzer->isNormalLevelSet());
}



TEST_F(SoundAnalyzerTest,
       GivenSilenceInitializedSoundAnalyzerWhenProperSilenceSampleIsProcessedThenSilenceReturnedButNotBefore) {
    int inputLevel = 100;
    initializeSoundLevel(soundAnalyzer, inputLevel);
    for (int i = 1; i < sampleSize; i++) {
        ASSERT_TRUE(soundAnalyzer->isSilenceLevelSet());
        ASSERT_TRUE(soundAnalyzer->processInput(getVariableInput(i, inputLevel)) == Sound::unknown);
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
//                make_tuple(silenceLevel + 20, Sound::silence),
//                make_tuple(failureLevel - 30, Sound::failure),
//                make_tuple(normalLevel + 40, Sound::normal),
//                make_tuple(silenceLevel - 21, Sound::unknown),
//                make_tuple(failureLevel + 31, Sound::unknown),
//                make_tuple(normalLevel - 41, Sound::unknown),
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


/*
TEST_F(SoundAnalyzerTest, GettingSilenceLevel) {
    initializeSoundLevel(soundAnalyzer, 141);
    initializeSoundLevel(soundAnalyzer, 134);
    initializeSoundLevel(soundAnalyzer, 129);
    ASSERT_FALSE(soundAnalyzer->isFailureLevelSet());
    ASSERT_FALSE(soundAnalyzer->isNormalLevelSet());
}
*/
