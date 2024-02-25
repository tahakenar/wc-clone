#ifndef WC_HPP
#define WC_HPP

#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <argh.h>
#include "definitions.hpp"

class Wc {
    public:
        Wc(char* argv[]);

        std::string getWcOutput();

        // TODO (tahakenar): Make them private later on
        void handleFlags();
        void handleFilename();
        void checkFileExistence();
        void openFile();
        void closeFile();

    private:
        argh::parser cmdl_;

        std::string filename_;
        std::ifstream file_;

        bool getBytes_;
        bool getLines_;
        bool getWords_;
        bool getChars_;

        unsigned long getNumOfBytes();
        unsigned long getNumOfLines();
        unsigned long getNumOfWords();
        unsigned long getNumOfChars();

        


    friend class WcTester;
};

#endif