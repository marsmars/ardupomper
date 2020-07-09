//
// Created by PGD384 on 7/9/2020.
//

#ifndef ARDUPOMPER_SOUNDANALYZER_H
#define ARDUPOMPER_SOUNDANALYZER_H

const int silenceInitSampleSize = 1000;
const int sampleSize = 100;

enum class Sound {
    silence, failure, normal, unknown
};

class SoundAnalyzer {
private:
    int silenceLevelInputCount = 0;
    int silenceLevel = 0;
public:
    Sound processInput(int input);

    bool isSilenceLevelSet() const;

    void initializeSilenceLevel(int input);

    void setSilenceLevel();

    bool itsTheLastSilenceInitReading() const;

    Sound getSoundFromInput(int input) const;

    bool isSampleSilence(int sample) const;

    int getAverage(int sum, int count) const;

    Sound getSound(int inputLevel) const;

    bool isSampleProcessed(int &input) const;
};


#endif //ARDUPOMPER_SOUNDANALYZER_H
