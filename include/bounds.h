#pragma once

#include <variant>
#include <date/date.h>

/////////////////////

struct never_t{ };

/////////////////////

struct bounds_t {
   using begin_t = date::year_month_day;
   using end_t = std::variant< never_t, date::year_month_day, int >;

   begin_t m_begin;
   end_t m_end;
};

/////////////////////
