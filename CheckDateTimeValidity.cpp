#include <array>
#include <stdexcept>


using namespace std;

class DateTime;

class DateError {
     public:
        enum ErrorType{
            SUCCESS,
            YEAR_IS_TO_SMALL, 
            YEAR_IS_TO_BIG,
            MONTH_IS_TO_SMALL,
            MONTH_IS_TO_BIG,
            DAY_IS_TO_SMALL,
            DAY_IS_TO_BIG,
            HOUR_IS_TO_SMALL,
            HOUR_IS_TO_BIG,
            MINUTE_IS_TO_SMALL,
            MINUTE_IS_TO_BIG,
            SECOND_IS_TO_SMALL,
            SECOND_IS_TO_BIG
        };

        DateError(ErrorType err):err_(err) {}
        ErrorType GetError() const{ return err_; }

private:
    ErrorType err_;

};




DateError CheckDateTimeValidity(const DateTime& dt) {
    if (dt.year < 1) {
        return DateError(DateError::YEAR_IS_TO_SMALL);
    }
    if (dt.year > 9999) {
        return  DateError(DateError::YEAR_IS_TO_BIG);
    }

    if (dt.month < 1) {
        return DateError(DateError::MONTH_IS_TO_SMALL);
    }
    if (dt.month > 12) {
        return DateError(DateError::MONTH_IS_TO_BIG);
    }

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dt.day < 1) {
        return DateError(DateError::DAY_IS_TO_SMALL);
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        return DateError(DateError::MONTH_IS_TO_BIG);
    }

    if (dt.hour < 0) {
        return DateError(DateError::HOUR_IS_TO_SMALL);
    }
    if (dt.hour > 23) {
        return DateError(DateError::HOUR_IS_TO_BIG);
    }

    if (dt.minute < 0) {
        return DateError(DateError::MINUTE_IS_TO_SMALL);
    }
    if (dt.minute > 59) {
        return DateError(DateError::MINUTE_IS_TO_BIG);
    }

    if (dt.second < 0) {
        return DateError(DateError::SECOND_IS_TO_SMALL);
    }
    if (dt.second > 59) {
        return DateError(DateError::SECOND_IS_TO_BIG);
    }
}