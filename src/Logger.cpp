//
// Created by PGD384 on 7/13/2020.
//
#ifdef ARDUINO_AVR_UNO
#include <Arduino.h>
#else
#include <iostream>
using std::cout;
#endif

#include "Logger.h"

void Logger::log(int value) {
#ifdef ARDUINO_AVR_UNO
    Serial.println(value);
#else
    cout << value;
#endif
}

void Logger::log(char *value) {
#ifdef ARDUINO_AVR_UNO
    Serial.println(value);
#else
    cout << value;
#endif
}
