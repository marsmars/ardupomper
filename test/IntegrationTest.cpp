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
    string filename = (R"(C:\Users\pgd384\Repo\ardupomper\ardupomper\test\testingFixture.csv)");
    ifstream data;

    int getInput();
    void reopenData();
public:
    IntegrationTest() : arduinoMock{arduinoMockInstance()},
                        data{ifstream(filename)} {}

    virtual ~IntegrationTest() { releaseArduinoMock(); }
};

void IntegrationTest::reopenData() {
    data.close();
    data.open(filename);
}


TEST_F(IntegrationTest, loadCSV)
{
    EXPECT_CALL(*arduinoMock, digitalWrite(_, _)).Times(AnyNumber());
    EXPECT_CALL(*arduinoMock, pinMode(_, _)).Times(AnyNumber());
    SoundAnalyzer analyzer;
    while(data.good())
        analyzer.processInput(getInput());
    ASSERT_TRUE(analyzer.isInitialized());
    reopenData();
    static int count = 0;
    while(data.good()) {
        switch (analyzer.processInput(getInput())) {
            case Sound::silence:
            case Sound::failure:
            case Sound::normal:
                count++;
                break;
            case Sound::unknown:
                break;
        }
    }
    ASSERT_EQ(6, count);
}

int IntegrationTest::getInput() {
    string line;
    getline(data, line);
    return stoi(line);
}
