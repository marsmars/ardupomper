#include <Arduino.h>
#include "main.h"
#include "Leds.h"
#include "Pomper.h"
#include "Button.h"
#include "LoopProcessor.h"

SoundAnalyzer *analyzer;
Leds *leds;
Button *button;
Pomper *pomper;
LoopProcessor *loopProcessor;


void mainLoop(LoopProcessor *loopProcessor, Button *button, Pomper *pomper, SoundAnalyzer *analyzer, Leds *leds) {
    button->isPressed() ? loopProcessor->stepPomperBack() : loopProcessor->processInput();
}

void setupMain() {
    Serial.begin(serialBaudRate);
    button = new Button;
    pomper = new Pomper;
    analyzer = new SoundAnalyzer();
    leds = new Leds(analyzer);
    loopProcessor = new LoopProcessor(pomper, analyzer, leds);
}

void setup() {
    setupMain();
}

void loop() {
    mainLoop(loopProcessor, button, pomper, analyzer, leds);
//    Serial.println(analogRead(A0));
}
