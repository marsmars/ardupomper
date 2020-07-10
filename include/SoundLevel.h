//
// Created by PGD384 on 7/10/2020.
//

#ifndef ARDUPOMPER_SOUNDLEVEL_H
#define ARDUPOMPER_SOUNDLEVEL_H

const int levelNotSet = -1;
const int sampleSize = 500;

class SoundLevel {
private:
    int inputCount = 0;
    int inputLevel = 0;
    int level = levelNotSet;
public:
    int getLevel() const;

    void setLevel(int level);

public:
    int getAverage(int sum, int count) const;
    bool isSampleProcessed(int &input);
    bool processInput(int input);
    bool isLevelSet() const;

    bool isLastInputInSample(int inputCount) const;

    bool isSampleAtLevel(int sample) const;
};


#endif //ARDUPOMPER_SOUNDLEVEL_H
