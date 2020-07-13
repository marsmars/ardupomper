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

void Logger::log(const char *value) {
#ifdef ARDUINO_AVR_UNO
    Serial.println(value);
#else
    cout << value;
#endif
}

void Logger::log(long value) {
#ifdef ARDUINO_AVR_UNO
    Serial.println(value);
#else
    cout << value;
#endif
}

void Logger::log(unsigned long value) {
#ifdef ARDUINO_AVR_UNO
    Serial.println(value);
#else
    cout << value;
#endif
}

void Logger::log(double value) {
#ifdef ARDUINO_AVR_UNO
    Serial.println(value);
#else
    cout << value;
#endif
}
