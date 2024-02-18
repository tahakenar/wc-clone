#include <gtest/gtest.h>

#include <string>
#include <fstream>
#include <filesystem>

#include "wc.hpp"

const std::string TEST_FILENAME = "test.txt";
const std::string TEST_DATA = "line1\nline2\nline3\nline4 secondWord\n";

const std::string GET_NUM_OF_BYTES = "-c " + TEST_FILENAME;
const std::string GET_NUM_OF_LINES = "-l " + TEST_FILENAME;
const std::string GET_NUM_OF_WORDS = "-w " + TEST_FILENAME;
const std::string GET_NUM_OF_CHARS = "-m " + TEST_FILENAME;
const std::string GET_OUTPUT_NO_OPTIONS = TEST_FILENAME;
const std::string GET_OUTPUT_NO_FILENAME = TEST_DATA;

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

class WcTester : public testing::Test {
    public:
        Wc* wc_obj_;
        void allocateWcObject(const std::string& input) {
            wc_obj_ = new Wc{input};
        }

        void clearWcObject() {
            delete wc_obj_;
        }

        unsigned int getBytes() {
            return wc_obj_->getNumOfBytes();
        }

        unsigned int getLines() {
            return wc_obj_->getNumOfLines();
        }

        unsigned int getWords() {
            return wc_obj_->getNumOfWords();
        }

        unsigned int getChars() {
            return wc_obj_->getNumOfChars();
        }
};

// TODO (tahakenar): Test case for invalid inputs (cannot parse properly)

// TODO (tahakenar): Test cases for no filename provided yet options

// Tests regarding member functions

TEST_F(WcTester, GetNumberOfBytes) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    allocateWcObject(GET_NUM_OF_BYTES);
    auto num_of_bytes = getBytes();
    clearWcObject();

    EXPECT_EQ(num_of_bytes, NUM_OF_BYTES);

    deleteTestFileIfExists(TEST_FILENAME);
}

TEST_F(WcTester, GetNumberOfLines) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    allocateWcObject(GET_NUM_OF_LINES);
    auto num_of_lines = getLines();
    clearWcObject();

    EXPECT_EQ(num_of_lines, NUM_OF_LINES);

    deleteTestFileIfExists(TEST_FILENAME);
}

TEST_F(WcTester, GetNumberOfWords) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    allocateWcObject(GET_NUM_OF_WORDS);
    auto num_of_words = getLines();
    clearWcObject();

    EXPECT_EQ(num_of_words, NUM_OF_WORDS);

    deleteTestFileIfExists(TEST_FILENAME);
}

TEST_F(WcTester, GetNumberOfChars) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    allocateWcObject(GET_NUM_OF_CHARS);
    auto num_of_chars = getChars();
    clearWcObject();

    EXPECT_EQ(num_of_chars, NUM_OF_CHARS);

    deleteTestFileIfExists(TEST_FILENAME);
}

// Tests regarding final output

TEST(WcTest, GetNumberOfBytesStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{GET_NUM_OF_BYTES};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NUM_OF_BYTES_OUT);

    deleteTestFileIfExists(TEST_FILENAME);
}


TEST(WcTest, GetNumberOfLinesStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{GET_NUM_OF_LINES};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NUM_OF_LINES_OUT);

    deleteTestFileIfExists(TEST_FILENAME);
}


TEST(WcTest, GetNumberOfWordsStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{GET_NUM_OF_WORDS};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NUM_OF_WORDS_OUT);

    deleteTestFileIfExists(TEST_FILENAME);
}


TEST(WcTest, GetNumberOfCharsStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{GET_NUM_OF_CHARS};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NUM_OF_CHARS_OUT);
    deleteTestFileIfExists(TEST_FILENAME);
}

TEST(WcTest, NoOptionsProvidedStdOut) {
    writeToTestFile(TEST_FILENAME, TEST_DATA);

    Wc wc{GET_OUTPUT_NO_OPTIONS};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, NO_OPTIONS_OUT);
    deleteTestFileIfExists(TEST_FILENAME);
}

TEST(WcTest, NoFilenameProvidedStdOut) {
    
    Wc wc{GET_OUTPUT_NO_FILENAME};
    auto out = wc.getWcOutput();
    
    EXPECT_EQ(out, NO_FILENAME_OUT);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
