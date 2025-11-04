#include "EmailUtils.h"
#include <regex>

namespace utils {

    bool EmailUtils::isEmailValido(const std::string& email) {
        static const std::regex pattern(R"(^[A-Za-z0-9._%+\-]+@[A-Za-z0-9.\-]+\.[A-Za-z]{2,}$)",
            std::regex::ECMAScript | std::regex::icase);
        return std::regex_match(email, pattern);
    }

}