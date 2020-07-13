//
// Created by PGD384 on 7/10/2020.
//

#ifndef ARDUPOMPER_SOUNDSAMPLE_H
#define ARDUPOMPER_SOUNDSAMPLE_H

const int notProcessed = -1;

class SoundSample {
    int inputCount = 0;
    long inputLevel = 0;
public:
    int processInput(int input);

    bool isProcessed();

    bool isLastInputInSample() const;

    int getAverage(int sum, int count) const;
};

#endif //ARDUPOMPER_SOUNDSAMPLE_H
