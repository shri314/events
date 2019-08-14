#pragma once

#include <variant>
#include <date/date.h>

/////////////////////

struct never_t{ };

/////////////////////

struct bounds_t {
   date::year_month_day m_begin;
   std::variant< never_t, date::year_month_day, int > m_end;
};

/////////////////////
