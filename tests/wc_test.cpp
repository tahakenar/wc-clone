#include <gtest/gtest.h>

#include <string>
#include <fstream>
#include <filesystem>

#include "wc.hpp"

const std::string TEST_FILENAME = "test.txt";
const std::string TEST_DATA = "line1\nline2\nline3\nline4 secondWord\n";

const unsigned int NUM_OF_BYTES = 35;
const unsigned int NUM_OF_LINES = 4;
const unsigned int NUM_OF_WORDS = 5;
const unsigned int NUM_OF_CHARS = 35;

const std::string NUM_OF_BYTES_OUT = "      35 " + TEST_FILENAME;
const std::string NUM_OF_LINES_OUT = "       4 " + TEST_FILENAME;
const std::string NUM_OF_WORDS_OUT = "       5 " + TEST_FILENAME;
const std::string NUM_OF_CHARS_OUT = "      35 " + TEST_FILENAME;
const std::string NO_OPTIONS_OUT = "       4       5      35 " + TEST_FILENAME;
const std::string NO_FILENAME_OUT = "       4       5      35";

 

// function to write to file
void writeToTestFile(const std::string& filename, const std::string& data) {
    std::ofstream ofs;
    ofs.open(filename);
    ofs << data;
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
    deleteTestFileIfExists(TEST_FILENAME);
}

TEST(WcTest, NoOptionsProvidedStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{""};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NO_OPTIONS_OUT);
    deleteTestFileIfExists(TEST_FILENAME);
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