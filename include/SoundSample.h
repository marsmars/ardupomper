//
// Created by PGD384 on 7/10/2020.
//

#ifndef ARDUPOMPER_SOUNDSAMPLE_H
#define ARDUPOMPER_SOUNDSAMPLE_H

const int notProcessed = -1;

class SoundSample {
    int inputCount = 0;
    unsigned long inputLevel = 0;
public:
    int processInput(int input);

    bool isComplete();

    bool isLastInputInSample() const;

    int getAverage(unsigned long sum, int count) const;

    int getLevel();
};

#endif //ARDUPOMPER_SOUNDSAMPLE_H
