#include "wc.hpp"

// TODO (tahakenar): remove iostream later
#include <iostream>

Wc::Wc(char* argv[]) : cmdl_{argv}, get_bytes_{false}, get_lines_{false}, get_words_{false}, get_chars_{false} {}

std::string Wc::getWcOutput() {
    std::stringstream output;

    try {
        // TODO (tahakenar): Handle stdin
        handleFlags();
        handleFilename();
        checkFileExistence();
        openFile();

        if (get_words_) {
            output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right << std::to_string(getNumOfWords());
        }
        if (get_lines_) {
            output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right << std::to_string(getNumOfLines());
        }
        // Gives the same output according to my locale
        if (get_bytes_ || get_chars_) {
            output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right << std::to_string(getNumOfBytes());
        }
        closeFile();
        output << " " << filename_;

    } catch (const std::runtime_error &err) {
        output.clear();
        output << err.what();
    } catch(...) {
        output.clear();
        output << wc_defs::err_msg::UNKNOWN_ERR;
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
    
    auto flags = cmdl_.flags();

    // If no flags provided, assume to print all options
    if (flags.size() == 0) {
        get_bytes_ = true;
        get_lines_ = true;
        get_words_ = true;
        get_chars_ = true;
        return;
    }

    auto eraseProvidedOpt = [](std::string& str, char opt) {
        auto end_iter = str.end();
        auto erase_iter = str.erase(std::remove(str.begin(), str.end(), opt), str.end());
        if (erase_iter != end_iter) {
            std::cout << "Deleted: " << opt << "\n";
            return true;
        }
        return false;
    };

    auto checkSingleFlag = [](std::multiset<std::string>& flag_set, const std::string& search_flag) {
        if (auto it = flag_set.find(search_flag); it != flag_set.end()) {
            flag_set.erase(it);
            return true;
        }
        return false;
    };

    get_bytes_ |= checkSingleFlag(flags, std::string{wc_defs::BYTE_OPT});
    get_lines_ |= checkSingleFlag(flags, std::string{wc_defs::LINE_OPT});
    get_chars_ |= checkSingleFlag(flags, std::string{wc_defs::CHAR_OPT});
    get_words_ |= checkSingleFlag(flags, std::string{wc_defs::WORD_OPT});

    // No flags must be seen after derivation...
    if (flags.size() > 0) {
        throw std::runtime_error(wc_defs::err_msg::INVALID_ARGS);
    }
}

void Wc::handleFilename() {
    auto positional_args = cmdl_.pos_args();
    // first arg is the program name (wc in this case)
    if (positional_args.size() < 2) {
        throw std::runtime_error(wc_defs::err_msg::NO_FILENAME_PROVIDED);
    } else if (positional_args.size() > 2) {
        throw std::runtime_error(wc_defs::err_msg::INVALID_ARGS);
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