//
// Created by PGD384 on 7/13/2020.
//
#ifdef ARDUINO_AVR_UNO
#include <Arduino.h>
#define PRINT(value) (Serial.println(value))
#else
#include <iostream>
#define PRINT(value) (cout << value << "\n")
//#define PRINT(value)
using std::cout;
#endif

#include "Logger.h"

void Logger::log(int value) {
    PRINT(value);
}

void Logger::log(const char *value) {
    PRINT(value);
}

void Logger::log(long value) {
    PRINT(value);
}

void Logger::log(unsigned long value) {
    PRINT(value);
}

void Logger::log(double value) {
    PRINT(value);
}
