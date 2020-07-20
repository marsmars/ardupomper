//
// Created by PGD384 on 7/4/2020.
//

#include <Arduino.h>
#include "Pomper.h"
#include <Stepper.h>


Stepper *stepper;

void Pomper::revolve() {
    stepper->step(stepsPerRevolution);
}

void Pomper::stepBack() {
    stepper->step(stepsBack);
}

Pomper::Pomper(Stepper *stepper) : stepper(stepper) {
    stepper->setSpeed(stepperSpeed);
}

Pomper::Pomper() {
    shouldReleaseStepper = true;
    stepper = new Stepper(stepsPerRevolution, 8, 10, 9, 11);
    stepper->setSpeed(stepperSpeed);
}

Pomper::~Pomper() {
    if (shouldReleaseStepper)
        delete stepper;
}
