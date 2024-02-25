#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <string>

namespace wc_defs
{
    constexpr int OUTPUT_WIDTH_PER_OPTION = 8; 

    const char BYTE_FLAG[] = "c";
    const char LINE_FLAG[] = "l";
    const char WORD_FLAG[] = "w";
    const char CHAR_FLAG[] = "m";

    namespace err_msg {
        const std::string NO_FILENAME_PROVIDED{"No filename provided"};
        const std::string INVALID_ARGS{"Invalid number of / types of arguments..."};
        const std::string NO_FILE_EXISTS{"No such file exists: "};
        const std::string CANNOT_OPEN_FILE{"Cannot open file: "};
    }
} // namespace wc_defs



#endif