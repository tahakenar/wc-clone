#include <gtest/gtest.h>

#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "wc.hpp"

char TEST_DATA[] = "line1\nline2\nline3\nline4 secondWord\n";

char TEST_FILENAME[] = "test.txt";
char NON_EXISTENT_FILENAME[] = "testo.txt";

char PROGRAM_NAME[] = "wc";

char BYTE_FLAG[] = "-c";
char LINE_FLAG[] = "-l";
char WORD_FLAG[] = "-w";
char CHAR_FLAG[] = "-m";
char INVALID_FLAG[] = "-i";

char* GET_NUM_OF_BYTES[] = {PROGRAM_NAME, BYTE_FLAG, TEST_FILENAME};
char* GET_NUM_OF_LINES[] = {PROGRAM_NAME, LINE_FLAG, TEST_FILENAME};
char* GET_NUM_OF_WORDS[] = {PROGRAM_NAME, WORD_FLAG, TEST_FILENAME};
char* GET_NUM_OF_CHARS[] = {PROGRAM_NAME, CHAR_FLAG, TEST_FILENAME};
char* GET_OUTPUT_NO_OPTIONS[] = {PROGRAM_NAME, TEST_FILENAME};
char* GET_OUTPUT_STDIN[] = {TEST_DATA};
char* INVALID_FLAGS[] = {PROGRAM_NAME, INVALID_FLAG, TEST_FILENAME};
char* NON_EXISTENT_FILE[] = {PROGRAM_NAME, BYTE_FLAG, NON_EXISTENT_FILENAME};
char* NO_FILENAME_PROVIDED[] = {PROGRAM_NAME, BYTE_FLAG};
char* TOO_MANY_ARGUMENTS[] = {PROGRAM_NAME, TEST_FILENAME, PROGRAM_NAME};

const unsigned int NUM_OF_BYTES = 35;
const unsigned int NUM_OF_LINES = 4;
const unsigned int NUM_OF_WORDS = 5;
const unsigned int NUM_OF_CHARS = 35;

auto add_numeric_out = [](const int& data) {
    std::stringstream ss;
    ss << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right << data << " ";
    return ss.str();
};

const std::string NUM_OF_BYTES_OUT = add_numeric_out(NUM_OF_BYTES) + std::string(TEST_FILENAME);
const std::string NUM_OF_LINES_OUT = add_numeric_out(NUM_OF_LINES) + std::string(TEST_FILENAME);
const std::string NUM_OF_WORDS_OUT = add_numeric_out(NUM_OF_WORDS) + std::string(TEST_FILENAME);
const std::string NUM_OF_CHARS_OUT = add_numeric_out(NUM_OF_CHARS) + std::string(TEST_FILENAME);
const std::string NO_OPTIONS_OUT = add_numeric_out(NUM_OF_LINES) + add_numeric_out(NUM_OF_WORDS) + add_numeric_out(NUM_OF_BYTES) + std::string(TEST_FILENAME);
const std::string STDIN_OUT = add_numeric_out(NUM_OF_LINES) + add_numeric_out(NUM_OF_WORDS) + add_numeric_out(NUM_OF_BYTES);

// function to write to file
void writeToTestFile(const char* filename, const char* data) {
    std::ofstream ofs;
    ofs.open(filename);
    ofs << std::string(data);
    ofs.close();
}

// function to delete file
void deleteTestFileIfExists(const char* filename) {
    try {
       std::filesystem::path test_file{filename};
       std::filesystem::remove(test_file);
    }
    catch(...){}
}

TEST(WcTest, NoFilenameProvided) {

    Wc wc{NO_FILENAME_PROVIDED};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, wc_defs::err_msg::NO_FILENAME_PROVIDED);
}

TEST(WcTest, InvalidNumberOfArgs) {

    Wc wc{TOO_MANY_ARGUMENTS};
    auto out = wc.getWcOutput();

    EXPECT_EQ(out, wc_defs::err_msg::INVALID_ARGS);
}

TEST(WcTest, NonExistentFilename) {
    
    Wc wc{NON_EXISTENT_FILE};
    auto out = wc.getWcOutput();

    std::string no_file_exists_out = wc_defs::err_msg::NO_FILE_EXISTS + std::string(NON_EXISTENT_FILENAME);
    EXPECT_EQ(out, no_file_exists_out);

}

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

TEST(WcTest, Stdin) {
    
    Wc wc{GET_OUTPUT_STDIN};
    auto out = wc.getWcOutput();
    
    EXPECT_EQ(out, STDIN_OUT);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
