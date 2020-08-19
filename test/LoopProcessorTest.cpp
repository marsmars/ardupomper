//
// Created by PGD384 on 7/20/2020.
//

#include <Arduino.h>
#include <tuple>
#include <LoopProcessor.h>

using testing::Test;
using testing::Return;
using testing::_;
using testing::TestWithParam;
using testing::Values;
using testing::NiceMock;
using std::tuple;
using std::make_tuple;

class SoundAnalyzerMock : public SoundAnalyzer {
public:
    MOCK_METHOD1(processInput, Sound(int));

    MOCK_CONST_METHOD0(isSilenceLevelSet, bool(void));

    MOCK_CONST_METHOD0(isFailureLevelSet, bool(void));

    MOCK_CONST_METHOD0(isNormalLevelSet, bool(void));

    MOCK_CONST_METHOD0(getSilenceLevel, double(void));

    MOCK_CONST_METHOD0(getFailureLevel, double(void));

    MOCK_CONST_METHOD0(getNormalLevel, double(void));

    MOCK_CONST_METHOD0(isInitialized, bool(void));
};

class PomperMock : public Pomper {
public:
    MOCK_METHOD0(stepBack, void(void));
    MOCK_METHOD0(revolve, void(void));
};

class LedsMock : public Leds {
public:
    LedsMock(SoundAnalyzer *analyzer) : Leds(analyzer) {}

    MOCK_METHOD0(changeStates, void(void));
};

class LoopProcessorTest : public TestWithParam<tuple<Sound, int>> {
protected:
    ArduinoMock *arduinoMock;
    PomperMock *pomper;
    NiceMock<SoundAnalyzerMock> *analyzer;
    NiceMock<LedsMock> *leds;
    LoopProcessor *main;

    virtual void SetUp() {
        EXPECT_CALL(*arduinoMock, pinMode(_, OUTPUT)).Times(3);
        pomper = new PomperMock();
        analyzer = new NiceMock<SoundAnalyzerMock>();
        leds = new NiceMock<LedsMock>(analyzer);
        main = new LoopProcessor(pomper, analyzer, leds);
    }

    virtual void TearDown() {
        delete main;
        delete leds;
        delete analyzer;
        delete pomper;
    }

public:

    LoopProcessorTest() : arduinoMock(arduinoMockInstance()) {}

    virtual ~LoopProcessorTest() {
        releaseArduinoMock();
    }

};

TEST_F(LoopProcessorTest, WhenStepPomperBackIsCalledThenPomperStepBackIsCalled) {
    EXPECT_CALL(*pomper, stepBack()).Times(1);
    main->stepPomperBack();
}

TEST_F(LoopProcessorTest, WhenProcessSoundIsCalledThenProperFunctionsAreCalled) {
    EXPECT_CALL(*arduinoMock, analogRead(_)).Times(1).WillOnce(Return(834));
    EXPECT_CALL(*analyzer, processInput(_)).Times(1).WillOnce(Return(Sound::unknown));
    EXPECT_CALL(*analyzer, isSilenceLevelSet()).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*analyzer, isInitialized()).Times(1).WillOnce(Return(false));
    main->processInput();
}

TEST_F(LoopProcessorTest, WhenChangeLedsStatesIsCalledThenLedChageStatesIsCalled) {
    EXPECT_CALL(*leds, changeStates()).Times(1);
    main->changeLedsStates();
}

TEST_F(LoopProcessorTest, GivenSilenceLevelInitializedWhenPrintIsCalledThenLevelIsRetrieved) {
    EXPECT_CALL(*analyzer, isSilenceLevelSet()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*analyzer, getSilenceLevel()).Times(1).WillOnce(Return(1));
    EXPECT_CALL(*analyzer, isFailureLevelSet()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*analyzer, getFailureLevel()).Times(1).WillOnce(Return(1));
    EXPECT_CALL(*analyzer, isNormalLevelSet()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*analyzer, getNormalLevel()).Times(1).WillOnce(Return(1));
    main->printInitializedLevels();
}


INSTANTIATE_TEST_CASE_P(
        soundReaction,
        LoopProcessorTest,
        Values(
                make_tuple(Sound::failure, 1),
                make_tuple(Sound::silence, 0),
                make_tuple(Sound::normal, 0),
                make_tuple(Sound::unknown, 0)));

TEST_P(LoopProcessorTest, GivenFailureSoundWhenProcessedThenPomperIsRevolvedButNotForOtherSounds){
    Sound sound = std::get<0>(GetParam());
    int callCount = std::get<1>(GetParam());
    EXPECT_CALL(*analyzer, isInitialized()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*pomper, revolve()).Times(callCount);
    main->processSound(sound);
}
