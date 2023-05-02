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

const int MIN_YEAR=0;
const int MAX_YEAR=9999;
const int MIN_MONTH=1;
const int MAX_MINTH=12;
const int MIN_DAY=1;
const int MIN_HOURS=0;
const int MAX_HOURS=23;
const int MIN_MINUTES=0;
const int MAX_MINUTES=59;
const int MIN_SECONDS=0;
const int MAX_SECONDS=59

DateError CheckDateTimeValidity(const DateTime& dt) {
    if (dt.year < MIN_YEAR) {
        return DateError(DateError::YEAR_IS_TO_SMALL);
    }
    if (dt.year > MAX_YEAR) {
        return  DateError(DateError::YEAR_IS_TO_BIG);
    }

    if (dt.month < MIN_MONTH) {
        return DateError(DateError::MONTH_IS_TO_SMALL);
    }
    if (dt.month > MAX_MONTH) {
        return DateError(DateError::MONTH_IS_TO_BIG);
    }

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dt.day < MIN_DAY) {
        return DateError(DateError::DAY_IS_TO_SMALL);
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        return DateError(DateError::MONTH_IS_TO_BIG);
    }

    if (dt.hour < MIN_HOURS) {
        return DateError(DateError::HOUR_IS_TO_SMALL);
    }
    if (dt.hour > MAX_HOURS) {
        return DateError(DateError::HOUR_IS_TO_BIG);
    }

    if (dt.minute < MIN_MINUTES) {
        return DateError(DateError::MINUTE_IS_TO_SMALL);
    }
    if (dt.minute > MAX_MINUTES) {
        return DateError(DateError::MINUTE_IS_TO_BIG);
    }

    if (dt.second < MIN_SECONDS) {
        return DateError(DateError::SECOND_IS_TO_SMALL);
    }
    if (dt.second > MAX_SECONDS) {
        return DateError(DateError::SECOND_IS_TO_BIG);
    }
}