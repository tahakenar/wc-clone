#include <gtest/gtest.h>

#include <string>
#include <fstream>
#include <filesystem>

#include "wc.hpp"

const std::string TEST_FILENAME = "test.txt";
const std::string TEST_DATA = "line1\nline2\nline3\nline4 secondWord\n";

// TODO (emir.kenar): Give actual values
const unsigned int NUM_OF_BYTES = 1;
const unsigned int NUM_OF_LINES = 1;
const unsigned int NUM_OF_WORDS = 1;
const unsigned int NUM_OF_CHARS = 1;

// TODO (emir.kenar): Give actual values
const std::string NUM_OF_BYTES_OUT = "";
const std::string NUM_OF_LINES_OUT = "";
const std::string NUM_OF_WORDS_OUT = "";
const std::string NUM_OF_CHARS_OUT = "";
const std::string NO_OPTIONS_OUT = "";
const std::string NO_FILENAME_OUT = "";

 

// function to write to file
void writeToTestFile(const std::string& filename, const std::string& data) {
    std::ofstream ofs;
    ofs.open(filename);
    ofs.close();
}

// function to delete file
void deleteTestFileIfExists(const std::string& filename) {
    try {
       std::filesystem::path test_file{filename};
       std::filesystem::remove(test_file);
    }
    catch(...){}
}


// Tests regarding member functions

// Tests regarding final output

TEST(WcTest, GetNumberOfBytesStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{""};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NUM_OF_BYTES_OUT);

    deleteTestFileIfExists(TEST_FILENAME);
}


TEST(WcTest, GetNumberOfLinesStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{""};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NUM_OF_LINES_OUT);

    deleteTestFileIfExists(TEST_FILENAME);
}


TEST(WcTest, GetNumberOfWordsStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{""};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NUM_OF_WORDS_OUT);

    deleteTestFileIfExists(TEST_FILENAME);
}


TEST(WcTest, GetNumberOfCharsStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{""};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NUM_OF_CHARS_OUT);
}

TEST(WcTest, NoOptionsProvidedStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{""};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NO_OPTIONS_OUT);
}

TEST(WcTest, NoFilenameProvidedStdOut) {
    
    Wc wc{TEST_DATA};
    auto out = wc.getWcOutput();
    
    EXPECT_EQ(out, NO_FILENAME_OUT);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}