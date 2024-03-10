#include "../include/date.h"
#include <string.h>

myDate::myDate(const std::string& str) { // hh:mm_dd.mm.yyyy
    hour = stoi(str.substr(0, 1));
    min = stoi(str.substr(3, 4));
    day = stoi(str.substr(6, 7));
    month = stoi(str.substr(9, 10));
    year = stoi(str.substr(12, 15));
} 

bool myDate::operator <(const myDate& other) const {
    if (year != other.year) return (year < other.year);
    if (month != other.month) return (month < other.month);
    if (day != other.day) return (day < other.day);
    if (hour != other.hour) return (hour < other.hour);
    return (min < other.min);
}

bool myDate::operator >(const myDate& other) const {
    return other < *this;
}

bool myDate::operator ==(const myDate& other) const {
    return !(*this < other) && !(other < *this);
}

bool myDate::operator !=(const myDate& other) const {
    return !(*this == other);
}

std::string myDate::to_string() const {
    std::string res;
    res += hour / 10 + '0';
    res += hour % 10 + '0';
    res += ':';
    res += min / 10 + '0';
    res += min % 10 + '0';
    res += '_';
    res += day / 10 + '0';
    res += day % 10 + '0';
    res += '.';
    res += month / 10 + '0';
    res += month % 10 + '0';
    res += '.';
    res += std::to_string(year);
    return res;
}