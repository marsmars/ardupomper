#include <Arduino.h>
#include "pomper.h"
#include "button.h"

void setup() {
    Serial.begin(9600);
    buttonSetup();
    pomperSetup();
}

void loop() {
    if (isButtonPressed()) {
        Serial.println("Pressed");
        pomperStepBack();
    }
    else {
        Serial.println(analogRead(A0), DEC);
    }
}
