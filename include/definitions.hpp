#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <string>

namespace wc_defs
{
    constexpr int OUTPUT_WIDTH_PER_OPTION = 8; 

    const char BYTE_OPT = 'c';
    const char LINE_OPT = 'l';
    const char WORD_OPT = 'w';
    const char CHAR_OPT = 'm';

    namespace err_msg {
        const std::string NO_FILENAME_PROVIDED{"No filename provided"};
        const std::string INVALID_ARGS{"Invalid number of / types of arguments..."};
        const std::string NO_FILE_EXISTS{"No such file exists: "};
        const std::string CANNOT_OPEN_FILE{"Cannot open file: "};
        const std::string UNKNOWN_ERR{"An unknown error has occured"};
    }
} // namespace wc_defs

#endif