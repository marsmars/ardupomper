////
//// Created by PGD384 on 7/8/2020.
////

#include <Arduino.h>
#include <Stepper.h>
#include "Pomper.h"

using namespace testing;

class StepperMock : public Stepper {
public:
    StepperMock() : Stepper(2038, 8, 10, 9, 11) {}

    MOCK_METHOD1(step, void(int));

    MOCK_METHOD1(setSpeed, void(long));
};

class PomperTest : public Test {
protected:
    ArduinoMock *arduinoMock;
    StepperMock *stepper;
    Pomper *pomper;
public:

    PomperTest() : arduinoMock{arduinoMockInstance()} {
        stepper = new StepperMock();
        EXPECT_CALL(*stepper, setSpeed(15));
        pomper = new Pomper(stepper);
    }

    virtual ~PomperTest() {
        delete pomper;
        delete stepper;
        releaseArduinoMock();
    }
};

TEST_F(PomperTest, GivenPomperWhenStepBackCalledThenStepperStepIsCalled) {
    EXPECT_CALL(*stepper, step(stepsBack));
    pomper->stepBack();
}

TEST_F(PomperTest, GivenPomperWhenRevolveCalledThenStepperStepIsCalled) {
    EXPECT_CALL(*stepper, step(stepsPerRevolution));
    pomper->revolve();
}