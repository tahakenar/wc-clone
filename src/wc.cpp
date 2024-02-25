#include "wc.hpp"

// TODO (tahakenar): remove iostream later
#include <iostream>

Wc::Wc(char* argv[]) : cmdl_{argv}, getBytes_{false}, getLines_{false}, getWords_{false}, getChars_{false} {


    
}

std::string Wc::getWcOutput() {
    std::stringstream output;

    try {
        handleFlags();
        handleFilename();
        checkFileExistence();
        openFile();

        if (getWords_) {
            output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right << std::to_string(getNumOfWords());
        }
        if (getLines_) {
            output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right << std::to_string(getNumOfLines());
        }
        if (getBytes_) {
            output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right << std::to_string(getNumOfBytes());
        }

        closeFile();
        output << " " << filename_;

    } catch (const std::runtime_error &err) {
        output.clear();
        output << err.what();
    } catch(...) {
        // .. handle exceptions to generate an informative output
    }

    return output.str();
}

void Wc::checkFileExistence() {
    if (!std::filesystem::exists(filename_)) {
        std::string err_msg = wc_defs::err_msg::NO_FILE_EXISTS + filename_;
        throw std::runtime_error(err_msg);
    }
}

void Wc::openFile() {
    file_.open(filename_);
    if (!file_.is_open()) {
        std::string err_msg = wc_defs::err_msg::CANNOT_OPEN_FILE + filename_;
        throw std::runtime_error(err_msg);
    }
}

void Wc::closeFile() {
    file_.close();
}

void Wc::handleFlags() {
    
    // TODO (tahakenar): Handle compounded flags

    auto flags = cmdl_.flags();

    if (flags.size() == 0) {
        getBytes_ = true;
        getLines_ = true;
        getWords_ = true;
        getChars_ = true;
    }

    if (auto it = flags.find(wc_defs::BYTE_FLAG); it != flags.end()) {
        getBytes_ = true;
        flags.erase(it);
    } 
    
    if (auto it = flags.find(wc_defs::LINE_FLAG); it != flags.end()) {
        getLines_ = true;
        flags.erase(it);
    }

    if (auto it = flags.find(wc_defs::WORD_FLAG); it != flags.end()) {
        getWords_ = true;
        flags.erase(it);
    }

    // TODO (tahakenar): Handle invalid cases
}

void Wc::handleFilename() {
    
    auto positional_args = cmdl_.pos_args();

    // first arg is the program name (wc in this case)
    if (positional_args.size() < 2) {
        // ... exception: lack of filename
    } else if (positional_args.size() > 2) {
        // ... exception: invalid number of positional args.
    } else {
        filename_ = std::string{positional_args[1]};
    }
}

unsigned long Wc::getNumOfBytes() {
    unsigned long num_of_bytes{0};
    num_of_bytes = std::filesystem::file_size(filename_);
    return num_of_bytes;
}

unsigned long Wc::getNumOfLines() {
    unsigned long num_of_lines{0};

    std::string line;
    while (std::getline(file_, line)) {
        num_of_lines++;
    }

    return num_of_lines;
}

unsigned long Wc::getNumOfWords() {
    unsigned long num_of_words{0};

    std::string line;
    while (std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            num_of_words++;
        }
    }

    return num_of_words;
}

unsigned long Wc::getNumOfChars() {
    unsigned long dummy{0};
    return dummy;
}