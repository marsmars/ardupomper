//
// Created by PGD384 on 7/13/2020.
//

#ifndef ARDUPOMPER_LOGGER_H
#define ARDUPOMPER_LOGGER_H


class Logger {
public:
    static void log(int value);

    static void log(long value);

    static void log(unsigned long value);

    static void log(double value);

    static void log(const char *value);
};


#endif //ARDUPOMPER_LOGGER_H
