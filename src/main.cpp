#include "rule.h"

#include <date/date.h>
#include <iostream>


/*
enum class day_t { Sat, Sun, Mon, Tue, Wed, Thu, Fri };
enum class month_t {
   jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

struct month_and_date_t {
   int date;
   month_t month;
};

struct weekly_t {
   int m_count;
   std::vector<day_t> m_on_days;
   bounds_t m_bounds;
};

struct monthly_by_day_t {
   int m_count;
   std::vector<int> m_on_ordinals;
   day_t on_day;
   bounds_t m_bounds;
};

struct monthly_by_dates_t {
   int m_count;
   std::vector<int> m_on_dates;
   bounds_t m_bounds;
};

struct yearly_t {
   int m_count;
   std::vector<month_and_date_t> m_on_month_dates;
   bounds_t m_bounds;
};
*/

/////////////////////

int main() {

   /*
      { "name": "Stand up", "repeat": "1 daily",                                "begins": "date", "ends": "never|date|12" },
      { "name": "Stand up", "repeat": "1 weekly",  "repeat_on": "Sat,Sun",      "begins": "date", "ends": "never|date|12" },
      { "name": "Stand up", "repeat": "1 monthly", "repeat_on": "2 Sat",        "begins": "date", "ends": "never|date|12" },
      { "name": "Stand up", "repeat": "1 monthly", "repeat_on": "14, 15",       "begins": "date", "ends": "never|date|12" },
      { "name": "Stand up", "repeat": "1 yearly",  "repeat_on": "2 Jan, 2 Feb", "begins": "date", "ends": "never|date|12" },
   */

   auto r1 = rule_t{
               title_t{"Stand up"},
               daily_t{1,
                  bounds_t{
                     date::day(29)/date::nov/date::year(2019),
                     date::day(5)/date::dec/date::year(2019)
                  }
               }
   };

   int limit = 10;
   for(auto d : r1.m_repeat) {
      std::cout << d << "\n";
      if(limit-- < 0)
         break;
   }
}
