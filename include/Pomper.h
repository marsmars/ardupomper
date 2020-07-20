//
// Created by PGD384 on 7/4/2020.
//

#ifndef ARDUPOMPER_POMPER_H
#define ARDUPOMPER_POMPER_H

#include "Stepper.h"

const int stepsPerRevolution = 2038;
const int stepsBack = -1;
const int stepperSpeed = 15;

class Pomper {
protected:
    Stepper *stepper;
    bool shouldReleaseStepper = false;
public:
    Pomper();

    Pomper(Stepper *stepper);

    virtual ~Pomper();

    virtual void revolve();

    virtual void stepBack();

};

#endif //ARDUPOMPER_POMPER_H
