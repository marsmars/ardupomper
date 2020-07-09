//
// Created by PGD384 on 7/4/2020.
//

#include "pomper.h"
#include <Stepper.h>

const int stepsPerRevolution = 2038;

Stepper stepper(stepsPerRevolution, 8, 10, 9, 11);

void pomperSetup() {
    stepper.setSpeed(15);
}

void pomperRevolve() {
    stepper.step(stepsPerRevolution);
}

void pomperStepBack() {
    stepper.step(-1);
}

