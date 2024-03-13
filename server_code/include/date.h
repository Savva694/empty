#pragma once

#include <iostream>

struct myDate {
private:
    size_t year;
    size_t month;
    size_t day;
    size_t hour;
    size_t min;

public:
    myDate() : year(0), month(0), day(0), hour(0), min(0) {}

    myDate(const std::string&);

    myDate(size_t year, size_t month, size_t day, size_t hour, size_t min) :
            year(year), month(month), day(day), hour(hour), min(min) {}

    bool operator <(const myDate&) const;

    bool operator >(const myDate&) const;

    bool operator ==(const myDate&) const;

    bool operator !=(const myDate&) const;

    std::string to_string() const;
    
    myDate get_only_date() const;
};
