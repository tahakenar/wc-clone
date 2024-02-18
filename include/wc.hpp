#ifndef WC_HPP
#define WC_HPP

#include <string>

class Wc {
    public:
        Wc(const std::string& input);
        std::string getWcOutput();
    private:
        unsigned long getNumOfBytes();
        unsigned long getNumOfLines();
        unsigned long getNumOfWords();
        unsigned long getNumOfChars();
};

#endif