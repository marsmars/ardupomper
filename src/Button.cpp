//
// Created by PGD384 on 7/4/2020.
//
#include <Arduino.h>
#include "Button.h"
const int buttonPin = 2;

bool Button::isPressed() {
    return getState() == LOW;
}

Button::Button() {
    pinMode(buttonPin, INPUT_PULLUP);
}

int Button::getState() {
    return(digitalRead(buttonPin));
}
