#ifndef STRING_UTIL
#define STRING_UTIL

#include <string>
#include <vector>

class StringUtil{
public:
    static std::string trim(std::string s) {
        if (s.empty()) {
            return s;
        }

        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
        return s;
    }

    static std::vector<std::string> split(const std::string& s, const std::string& c) {
        std::vector<std::string> result;

        std::string::size_type pos1, pos2;
        pos2 = s.find(c);
        pos1 = 0;
        while (std::string::npos != pos2) {
            result.push_back(s.substr(pos1, pos2 - pos1));

            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if (pos1 != s.length())
            result.push_back(s.substr(pos1));

        return result;
    }
};

#endif // !STRING_UTIL

