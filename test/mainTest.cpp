//
// Created by PGD384 on 7/16/2020.
//

#include <Arduino.h>
#include <tuple>
#include <LoopProcessor.h>
#include "main.h"
#include "Button.h"

using testing::Test;
using testing::Return;
using testing::_;
using testing::TestWithParam;
using testing::Values;
using testing::NiceMock;
using std::tuple;
using std::make_tuple;

class ButtonMock : public Button {
public:
    ButtonMock() {}

    MOCK_METHOD0(isPressed, bool(void));
};

class LoopProcessorMock : public LoopProcessor {
public:
    LoopProcessorMock(Pomper *pomper, SoundAnalyzer *analyzer, Leds *leds) : LoopProcessor(pomper, analyzer,
                                                                                           leds) {}
    MOCK_METHOD0(stepPomperBack, void(void));
    MOCK_METHOD0(processInput, void(void));
};

class mainTest : public TestWithParam<tuple<bool, int>> {
protected:
    ArduinoMock *arduinoMock;
    ButtonMock *button;
    LoopProcessorMock *loopProcessor;

    virtual void SetUp() {
        EXPECT_CALL(*arduinoMock, pinMode(_, INPUT_PULLUP)).Times(1);
        button = new ButtonMock();
        loopProcessor = new LoopProcessorMock(nullptr, nullptr, nullptr);
    }

    virtual void TearDown() {
        delete loopProcessor;
        delete button;
    }

public:

    mainTest() : arduinoMock(arduinoMockInstance()) {}

    virtual ~mainTest() {
        releaseArduinoMock();
    }

};

INSTANTIATE_TEST_CASE_P(
        stepBackTest,
        mainTest,
        Values(
                make_tuple(true, 1),
                make_tuple(false, 0)));


TEST_P(mainTest, WhenButtonPressedOrNotThenStepBackIsCalledOrNot) {
    bool buttonPressed = std::get<0>(GetParam());
    int callCount = std::get<1>(GetParam());
    EXPECT_CALL(*button, isPressed()).Times(1).WillOnce(Return(buttonPressed));
    EXPECT_CALL(*loopProcessor, stepPomperBack()).Times(callCount);
    EXPECT_CALL(*loopProcessor, processInput()).Times(1 - callCount);
    mainLoop(loopProcessor, button, nullptr, nullptr, nullptr);
}