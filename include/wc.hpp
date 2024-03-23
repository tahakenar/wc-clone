#ifndef WC_HPP
#define WC_HPP

#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <argh.h>
#include "definitions.hpp"

class Wc {
    public:
        Wc(char* argv[]);
        std::string getWcOutput();

    private:
        argh::parser cmdl_;

        std::string filename_;

        std::stringstream input_;
        std::ifstream file_;

        bool get_bytes_;
        bool get_lines_;
        bool get_words_;
        bool get_chars_;

        unsigned long getNumOfBytes();
        unsigned long getNumOfLines();
        unsigned long getNumOfWords();
        unsigned long getNumOfChars();

        void handleFlags();
        void handleFilename();

        void getStdin();
        void readFile();

        void checkFileExistence();
        void openFile();
        void closeFile();
};

#endif