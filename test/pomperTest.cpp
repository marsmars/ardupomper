////
//// Created by PGD384 on 7/8/2020.
////
//
//#include <Arduino.h>
//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#include <Stepper.h>
//#include "pomper.h"
//
//using namespace testing;
//
//class PomperMock : public Stepper {
//public:
//    PomperMock() : Stepper(2038, 8, 10, 9, 11) {}
//    PomperMock(int a, int b, int c, int d, int e) : Stepper(a, b, c, d, e) {}
//
//    MOCK_METHOD1(step, void(int));
//    MOCK_METHOD1(setSpeed, void(long));
//};
//
//class PomperTest : public Test {
//protected:
//    ArduinoMock& arduinoMock;
//    PomperMock& pomperMock;
//public:
//    virtual ~PomperTest() {
//        delete &pomperMock;
//    }
//
//    PomperTest() : arduinoMock {*arduinoMockInstance()}, pomperMock {*(new PomperMock())} {}
//};
//
