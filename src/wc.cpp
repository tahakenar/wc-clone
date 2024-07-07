#include "wc.hpp"

#include <iostream>
#include <sstream>

Wc::Wc(char *argv[])
    : cmdl_{argv}, get_bytes_{false}, get_lines_{false}, get_words_{false},
      get_chars_{false} {}

std::string Wc::getWcOutput() {
  input_.clear();
  std::stringstream output;
  try {
    handleFlags();

    auto positional_args = cmdl_.pos_args();

    if (positional_args.size() < 2) {
      getStdin();
    } else {
      filename_ = std::string{positional_args[1]};
      checkFileExistence();
      readFile();
    }
    if (get_lines_) {
      output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right
             << std::to_string(getNumOfLines());
    }
    if (get_words_) {
      output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right
             << std::to_string(getNumOfWords());
    }
    // Gives the same output according to my locale
    if (get_bytes_ || get_chars_) {
      output << std::setw(wc_defs::OUTPUT_WIDTH_PER_OPTION) << std::right
             << std::to_string(getNumOfBytes());
    }
    output << " " << filename_;
  } catch (const std::runtime_error &err) {
    output.clear();
    output << err.what();
  } catch (...) {
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

void Wc::getStdin() {
  std::string line;
  while (std::getline(std::cin, line)) {
    input_ << line << '\n';
  }
}

void Wc::readFile() {
  file_.open(filename_);
  if (!file_.is_open()) {
    std::string err_msg = wc_defs::err_msg::CANNOT_OPEN_FILE + filename_;
    throw std::runtime_error(err_msg);
  }
  std::string line;
  while (std::getline(file_, line)) {
    input_ << line << '\n';
  }
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

  for (auto f : flags) {
    if (auto found = f.find(wc_defs::BYTE_OPT) != std::string::npos) {
      get_bytes_ = true;
      f.erase(std::remove(f.begin(), f.end(), wc_defs::BYTE_OPT), f.end());
    }

    if (auto found = f.find(wc_defs::CHAR_OPT) != std::string::npos) {
      get_chars_ = true;
      f.erase(std::remove(f.begin(), f.end(), wc_defs::CHAR_OPT), f.end());
    }

    if (auto found = f.find(wc_defs::LINE_OPT) != std::string::npos) {
      get_lines_ = true;
      f.erase(std::remove(f.begin(), f.end(), wc_defs::LINE_OPT), f.end());
    }

    if (auto found = f.find(wc_defs::WORD_OPT) != std::string::npos) {
      get_words_ = true;
      f.erase(std::remove(f.begin(), f.end(), wc_defs::WORD_OPT), f.end());
    }

    if (f.size() > 0) {
      throw std::runtime_error(wc_defs::err_msg::INVALID_ARGS);
    }
  }
}

unsigned long Wc::getNumOfBytes() {
  unsigned long num_of_bytes{0};
  num_of_bytes = input_.str().length();
  return num_of_bytes;
}

unsigned long Wc::getNumOfLines() {
  unsigned long num_of_lines{0};
  std::string line;
  while (std::getline(input_, line)) {
    num_of_lines++;
  }
  input_.clear();
  input_.seekg(0, std::ios::beg);
  return num_of_lines;
}

unsigned long Wc::getNumOfWords() {
  unsigned long num_of_words{0};
  std::string line;
  while (std::getline(input_, line)) {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
      num_of_words++;
    }
  }
  input_.clear();
  input_.seekg(0, std::ios::beg);
  return num_of_words;
}

unsigned long Wc::getNumOfChars() {
  unsigned long dummy{0};
  return dummy;
}