#include <iostream>

struct Date {
private:
    size_t year;
    size_t month;
    size_t day;
    size_t hour;
    size_t min;

public:
    Date() : year(0), month(0), day(0), hour(0), min(0) {}
    Date(size_t year, size_t month, size_t day, size_t hour, size_t min) :
            year(year), month(month), day(day), hour(hour), min(min) {}
    operator std::string() const;
    bool operator <(const Date&) const;
    bool operator >(const Date&) const;
    bool operator ==(const Date&) const;
    bool operator !=(const Date&) const;
};