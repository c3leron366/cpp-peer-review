#include <array>

struct Constraints
{
public:
    Constraints(const DateTime& dt)
    {
        const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
        const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        max_.day = max.month_lengths[dt.month - 1];
        dt_ = dt;
    }

    

    void Check()
    {
        if (dt_.year < min_.year) {
            throw domain_error("year is too small"s);
        }
        if (dt_.year > max_.year) {
            throw domain_error("year is too big"s);
        }

        if (dt_.month < min_.month) {
            throw domain_error("month is too small"s);
        }
        if (dt_.month > max_.month) {
            throw domain_error("month is too big"s);
        }

        if (dt_.day < min_.day) {
            throw domain_error("day is too small"s);
        }
        if (dt_.day > max_.day) {
            throw domain_error("day is too big"s);
        }

        if (dt_.hour < min_.hour) {
            throw domain_error("hour is too small"s);
        }
        if (dt_.hour > max.hour) {
            throw domain_error("hour is too big"s);
        }

        if (dt_.minute < min_.minute) {
            throw domain_error("minute is too small"s);
        }
        if (dt_.minute > max_.minute) {
            throw domain_error("minute is too big"s);
        }

        if (dt_.second < min_.second) {
            throw domain_error("second is too small");
        }
        if (dt_.second > max_.second) {
            throw domain_error("second is too big"s);
        }
    }

    DateTime min_{
        .year = 1,
        .month = 1,
        .day = 1,
        .hour = 0,
        .minute = 0,
        .second = 0
    };
    DateTime max_{
        .year = 9999,
        .month = 12,
        .day = 31,
        .hour = 23,
        .minute = 59,
        .second = 59
    };
    DateTime dt_;
};


void CheckDateTimeValidity(const DateTime& dt) 
{
    Constraints c(dt);
    c.Check();
} 

