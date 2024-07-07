#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <string>

namespace wc_defs {
constexpr int OUTPUT_WIDTH_PER_OPTION = 8;

const char BYTE_OPT = 'c';
const char LINE_OPT = 'l';
const char WORD_OPT = 'w';
const char CHAR_OPT = 'm';

const char OPT_ARR[4] = {BYTE_OPT, LINE_OPT, WORD_OPT, CHAR_OPT};

namespace err_msg {
const std::string INVALID_ARGS{"Invalid number of / types of arguments..."};
const std::string NO_FILE_EXISTS{"No such file exists: "};
const std::string CANNOT_OPEN_FILE{"Cannot open file: "};
const std::string UNKNOWN_ERR{"An unknown error has occured"};
} // namespace err_msg
} // namespace wc_defs

#endif