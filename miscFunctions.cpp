#include "Question.hpp"

int stringToInt(const std::string& str) {
    int num = 0;
    int sign = 1;
    size_t i = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (i < str.size()) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        num = num * 10 + (str[i] - '0');
        i++;
    }

    return num * sign;
}