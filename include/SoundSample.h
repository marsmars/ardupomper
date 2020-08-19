//
// Created by PGD384 on 7/10/2020.
//

#ifndef ARDUPOMPER_SOUNDSAMPLE_H
#define ARDUPOMPER_SOUNDSAMPLE_H

const int sampleSize = 20000;
const int notProcessed = -1;
const double precisionPercent = 40;


class SoundSample {
    int inputCount = 0;
    double inputLevel = 0;
    double baseLevel = 0.0;
    double sampleLevel = 0.0;
public:
    double processInput(int input);

    bool isComplete();

    bool isLastInputInSample() const;

    bool isAtLevel(double level) const;

    double getAverage(unsigned long sum, int count) const;

    double getLevel() const;

    double setSampleLevel();
};

#endif //ARDUPOMPER_SOUNDSAMPLE_H
