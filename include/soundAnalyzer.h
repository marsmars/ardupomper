//
// Created by PGD384 on 7/9/2020.
//

#ifndef ARDUPOMPER_SOUNDANALYZER_H
#define ARDUPOMPER_SOUNDANALYZER_H

const int numberOfInitSamplesNeeded = 1000;

enum class Sound { silence, failure, normal, unknown};

class SoundAnalyzer {
private:
    int silenceLevelSampleCount = 0;
    int silenceLevel = 0;
    bool silenceInitialized = false;
public:
    Sound processSample(int sample);

    bool isSilenceLevelSet();

    void initializeSilenceLevel(int sample);

    bool itsTheLastSilenceInitSample() const;

    void setSilenceLevel();
};


#endif //ARDUPOMPER_SOUNDANALYZER_H
