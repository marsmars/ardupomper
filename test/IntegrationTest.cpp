//
// Created by PGD384 on 7/22/2020.
//

#include <Arduino.h>
#include <tuple>
#include <fstream>
#include <LoopProcessor.h>

using testing::Test;
using testing::TestWithParam;
using testing::Values;
using testing::_;
using testing::Return;
using testing::AnyNumber;
using std::tuple;
using std::make_tuple;
using std::ifstream;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stoi;

class IntegrationTest : public TestWithParam<tuple<int, bool>> {
protected:
    ArduinoMock *arduinoMock;
    string basicFixtureFilename = (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\basicFixture.csv)");
    string silenceFixtureFilename = (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture.csv)");
    ifstream basicFixture;
    ifstream silenceFixture;

    int getBasicInput();
    void reopenBasicFixture();
    int getSilenceInput();
    void reopenSilenceFixture();
public:
    IntegrationTest() : arduinoMock{arduinoMockInstance()},
                        basicFixture{ifstream(basicFixtureFilename)},
                        silenceFixture{ifstream(silenceFixtureFilename)} {}

    virtual ~IntegrationTest() { releaseArduinoMock(); }
};

void IntegrationTest::reopenBasicFixture() {
    basicFixture.close();
    basicFixture.open(basicFixtureFilename);
}

void IntegrationTest::reopenSilenceFixture() {
    silenceFixture.close();
    silenceFixture.open(silenceFixtureFilename);
}

int IntegrationTest::getBasicInput() {
    string line;
    getline(basicFixture, line);
    return stoi(line);
}

int IntegrationTest::getSilenceInput() {
//    static int count = 1;
    string line;
    getline(silenceFixture, line);
//    cout << count++ << ". " << line << endl;
    return stoi(line);
}


TEST_F(IntegrationTest, checkBasicFixtureWithAllSounds)
{
    EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
    EXPECT_CALL(*arduinoMock, pinMode(_, _)).Times(AnyNumber());
    SoundAnalyzer analyzer;
    while(basicFixture.good())
        analyzer.processInput(getBasicInput());
    ASSERT_TRUE(analyzer.isInitialized());
    reopenBasicFixture();
    static int count = 0;
    while(basicFixture.good()) {
        switch (analyzer.processInput(getBasicInput())) {
            case Sound::silence:
            case Sound::failure:
            case Sound::normal:
                count++;
                break;
            case Sound::unknown:
                break;
        }
    }
    ASSERT_EQ(4, count);
}

TEST_F(IntegrationTest, checkSileceFixtureWithSilenceOnly)
{
    EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
    EXPECT_CALL(*arduinoMock, pinMode(_, _)).Times(AnyNumber());
    SoundAnalyzer analyzer;
    while(silenceFixture.good())
        analyzer.processInput(getSilenceInput());
    ASSERT_FALSE(analyzer.isInitialized());
}

