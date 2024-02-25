#ifndef WC_HPP
#define WC_HPP

#include <string>

#include <argh.h>

class Wc {
    public:
        Wc(char* argv[]);
        std::string getWcOutput();
    private:
        unsigned long getNumOfBytes();
        unsigned long getNumOfLines();
        unsigned long getNumOfWords();
        unsigned long getNumOfChars();

        // TODO (emir.kenar): Add CLI parser
        

        bool getBytes;
        bool getLines;
        bool getWords;
        bool getChars;
    friend class WcTester;
};

#endif