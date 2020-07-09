//
// Created by PGD384 on 7/4/2020.
//
#include <Arduino.h>
#include "button.h"
const int buttonPin = 2;

void buttonSetup() {
    pinMode(buttonPin, INPUT_PULLUP);
}

int getButtonState() {
    return(digitalRead(buttonPin));
}

bool isButtonPressed(){
    return getButtonState() == HIGH;
}
