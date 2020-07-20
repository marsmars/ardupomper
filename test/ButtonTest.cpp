//
// Created by PGD384 on 7/7/2020.
//

#include <Arduino.h>
#include <tuple>
#include "Button.h"

using testing::Test;
using testing::TestWithParam;
using testing::Values;
using testing::_;
using testing::Return;
using std::tuple;
using std::make_tuple;

class ButtonTest : public TestWithParam<tuple<int, bool>> {
protected:
    ArduinoMock *arduinoMock;
    Button *button;
public:
    ButtonTest() : arduinoMock{arduinoMockInstance()} {
        EXPECT_CALL(*arduinoMock, pinMode(_, INPUT_PULLUP)).Times(1);
        button = new Button();
    }

    virtual ~ButtonTest() {
        releaseArduinoMock();
        delete button;
    }
};

INSTANTIATE_TEST_CASE_P(
        isButtonPressedTests,
        ButtonTest,
        Values(
                make_tuple(LOW, true),
                make_tuple(HIGH, false)));

TEST_P(ButtonTest, GiveButtonWhenStateIsSetThenButtonIsPressedOrNot) {
    int state = std::get<0>(GetParam());
    bool expected = std::get<1>(GetParam());
    EXPECT_CALL(*arduinoMock, digitalRead(_)).WillRepeatedly(Return(state));
    ASSERT_EQ(expected, button->isPressed());
}