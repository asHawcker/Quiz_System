#include "Question.hpp"

int stringToInt(const char* str){
        int num = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        ++str;
    }
    
    while (*str) {
        num = num * 10 + (*str - '0');
        ++str;
    }
    return num * sign;
}