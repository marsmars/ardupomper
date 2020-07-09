//
// Created by PGD384 on 7/7/2020.
//

#include <Arduino.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include "button.h"

using namespace testing;

class SoundAnalyzerTest : public TestWithParam<std::tuple<int, bool>> {
protected:
    ArduinoMock& arduinoMock;
public:
    SoundAnalyzerTest() : arduinoMock {*arduinoMockInstance()} {}

};

TEST_F(SoundAnalyzerTest, GiveButtonWhenInitializedThenPiModeIsCalleWithINPUT_PULLUP){
    EXPECT_CALL(arduinoMock, pinMode(_, INPUT_PULLUP)).Times(1);
    buttonSetup();
}


TEST_P(SoundAnalyzerTest, GiveButtonWhenStateIsSetThenButtonIsPressedOrNot) {
    int state = std::get<0>(GetParam());
    bool expected = std::get<1>(GetParam());
    EXPECT_CALL(arduinoMock, digitalRead(_)).WillRepeatedly(Return(state));
    ASSERT_EQ(expected, isButtonPressed());
}

INSTANTIATE_TEST_CASE_P(
        isButtonPressedTests,
        SoundAnalyzerTest,
        Values(
                std::make_tuple(HIGH, true),
                std::make_tuple(LOW, false)));