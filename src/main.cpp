#include <Arduino.h>
#include "Leds.h"
#include "pomper.h"
#include "button.h"
#include "Logger.h"

SoundAnalyzer *analyzer;
Leds *leds;

void setup() {
    Serial.begin(9600);
    buttonSetup();
    pomperSetup();
    ledsSetup();
    analyzer = new SoundAnalyzer();
    leds = new Leds(analyzer);
}

void loop() {
    static bool silencePrinted = false;
    static bool failurePrinted = false;
    static bool normalPrinted = false;
    if (isButtonPressed()) {
        pomperStepBack();
    } else {
        Sound sound = analyzer->processInput(analogRead(A0));
        leds->changeStates();
        if (analyzer->isSilenceLevelSet() && !silencePrinted){
            Logger::log("--Silence level:");
            Logger::log(analyzer->getSilenceLevel());
            silencePrinted = true;
        }
        if (analyzer->isFailureLevelSet() && !failurePrinted){
            Logger::log("--Failure level:");
            Logger::log(analyzer->getFailureLevel());
            failurePrinted = true;
        }
        if (analyzer->isNormalLevelSet() && !normalPrinted){
            Logger::log("--Normal level:");
            Logger::log(analyzer->getNormalLevel());
            normalPrinted = true;
        }
        if (analyzer->isInitialized())
            switch (sound) {
                case Sound::silence:
                    Logger::log("Silence detected");
                    break;
                case Sound::failure:
                    Logger::log("Failure detected");
                    break;
                case Sound::normal:
                    Logger::log("Normal sound detected");
                    break;
                case Sound::unknown:
                    break;
            };
//        Serial.println(analogRead(A0));
    }
}
