//
// Created by PGD384 on 7/7/2020.
//

#include <Arduino.h>
#include <tuple>
#include <memory>
#include "button.h"

using testing::Test;
using testing::TestWithParam;
using testing::Values;
using testing::_;
using testing::Return;
using std::tuple;
using std::make_tuple;
using std::unique_ptr;

class ButtonTest : public TestWithParam<tuple<int, bool>> {
protected:
     ArduinoMock& arduinoMock;
public:
    ButtonTest() : arduinoMock {*arduinoMockInstance()} {}

};

TEST_F(ButtonTest, GiveButtonWhenInitializedThenPiModeIsCalleWithINPUT_PULLUP){
    EXPECT_CALL(arduinoMock, pinMode(_, INPUT_PULLUP)).Times(1);
    buttonSetup();
}


TEST_P(ButtonTest, GiveButtonWhenStateIsSetThenButtonIsPressedOrNot) {
    int state = std::get<0>(GetParam());
    bool expected = std::get<1>(GetParam());
    EXPECT_CALL(arduinoMock, digitalRead(_)).WillRepeatedly(Return(state));
    ASSERT_EQ(expected, isButtonPressed());
}

INSTANTIATE_TEST_CASE_P(
        isButtonPressedTests,
        ButtonTest,
        Values(
                make_tuple(HIGH, true),
                make_tuple(LOW, false)));