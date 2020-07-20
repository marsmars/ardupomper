//
// Created by PGD384 on 7/11/2020.
//

#include <Arduino.h>
#include <SoundAnalyzer.h>
#include "Leds.h"
#include "SoundAnalyzerTest.h"

using testing::Test;
using testing::_;

class LedsTest : public Test {
protected:
    ArduinoMock* arduinoMock;
    SoundAnalyzer *analyzer;
    Leds *leds;

    virtual void SetUp() {
        EXPECT_CALL(*arduinoMock, pinMode(silenceLed, OUTPUT)).Times(1);
        EXPECT_CALL(*arduinoMock, pinMode(normalLed, OUTPUT)).Times(1);
        EXPECT_CALL(*arduinoMock, pinMode(failureLed, OUTPUT)).Times(1);
        analyzer = new SoundAnalyzer;
        leds = new Leds(analyzer);
    }

    virtual void TearDown() {
        delete leds;
        delete analyzer;

    }
public:
    LedsTest() : arduinoMock {arduinoMockInstance()} {}

    virtual ~LedsTest() {
        releaseArduinoMock();
    }

};

TEST_F(LedsTest, GivenNonSilenceInitializedSoundAnalyzerWhenLedsStatesChangedThenSilenceLedIsTurnedOff) {
    EXPECT_CALL(*arduinoMock, digitalWrite(silenceLed, LOW));
    EXPECT_CALL(*arduinoMock, digitalWrite(failureLed, LOW));
    EXPECT_CALL(*arduinoMock, digitalWrite(normalLed, LOW));
    leds->changeStates();
}

TEST_F(LedsTest, GivenSilenceInitializedSoundAnalyzerWhenLedsStatesChangedThenSilenceLedIsSet) {
    EXPECT_CALL(*arduinoMock, digitalWrite(silenceLed, HIGH));
    EXPECT_CALL(*arduinoMock, digitalWrite(failureLed, LOW));
    EXPECT_CALL(*arduinoMock, digitalWrite(normalLed, LOW));
    initializeSoundLevel(analyzer, silenceLevel);
    leds->changeStates();
}


TEST_F(LedsTest, GivenNormalInitializedSoundAnalyzerWhenLedsStatesChangedThenSilenceLedIsSet) {
    EXPECT_CALL(*arduinoMock, digitalWrite(silenceLed, HIGH));
    EXPECT_CALL(*arduinoMock, digitalWrite(failureLed, HIGH));
    EXPECT_CALL(*arduinoMock, digitalWrite(normalLed, LOW));
    initializeSoundLevel(analyzer, silenceLevel);
    initializeSoundLevel(analyzer, failureLevel);
    leds->changeStates();
}

TEST_F(LedsTest, GivenNonNormalInitializedSoundAnalyzerWhenLedsStatesChangedThenSilenceLedIsTurnedOff) {
    EXPECT_CALL(*arduinoMock, digitalWrite(silenceLed, HIGH));
    EXPECT_CALL(*arduinoMock, digitalWrite(failureLed, HIGH));
    EXPECT_CALL(*arduinoMock, digitalWrite(normalLed, HIGH));
    initializeSoundLevel(analyzer, silenceLevel);
    initializeSoundLevel(analyzer, failureLevel);
    initializeSoundLevel(analyzer, normalLevel);
    leds->changeStates();
}
