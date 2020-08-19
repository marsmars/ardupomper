//
// Created by PGD384 on 7/25/2020.
//

#include <Arduino.h>
#include <tuple>
#include <fstream>
#include <LoopProcessor.h>

using testing::Test;
using testing::TestWithParam;
using testing::Values;
using testing::_;
//using testing::Return;
using testing::AnyNumber;
using std::ifstream;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stoi;

class SilenceIntTest : public TestWithParam<string> {
protected:
    ArduinoMock *arduinoMock;

public:
    SilenceIntTest() : arduinoMock{arduinoMockInstance()} {}

    virtual ~SilenceIntTest() { releaseArduinoMock(); }
};



INSTANTIATE_TEST_CASE_P(
        silenceLevelsTest,
        SilenceIntTest,
        Values(
                (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture020.csv)"),
                (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture060.csv)"),
                (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture120.csv)"),
                (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture200.csv)"),
                (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture300.csv)"),
                (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture500.csv)"),
                (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture800.csv)"),
                (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\silenceFixture999.csv)")));


TEST_P(SilenceIntTest, checkSileceFixtureWithSilenceOnly)
{
    EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
    EXPECT_CALL(*arduinoMock, pinMode(_, _)).Times(AnyNumber());
    SoundAnalyzer analyzer;
    ifstream fixture(GetParam());
    while(fixture.good()){
        string line;
        getline(fixture, line);
        analyzer.processInput(stoi(line));
    }
    cout << GetParam() << endl;
//    ASSERT_TRUE(analyzer.isSilenceLevelSet());
//    ASSERT_FALSE(analyzer.isFailureLevelSet());
//    ASSERT_FALSE(analyzer.isNormalLevelSet());
}
