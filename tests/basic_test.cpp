#include "rule.h"

#include <gtest/gtest.h>

#include <vector>
#include <date/date.h>

TEST(test_basic, check_daily_case1) {

   auto r1 = rule_t{
               title_t{"Stand up"},
               daily_t{1,
                  bounds_t{
                     date::day(29)/date::nov/date::year(2019),
                     date::day(5)/date::dec/date::year(2019)
                  }
               }
   };

   std::vector<date::year_month_day> expected = {
      date::day(29)/date::nov/date::year(2019),
      date::day(30)/date::nov/date::year(2019),
      date::day(1)/date::dec/date::year(2019),
      date::day(2)/date::dec/date::year(2019),
      date::day(3)/date::dec/date::year(2019),
      date::day(4)/date::dec/date::year(2019),
      date::day(5)/date::dec/date::year(2019),
   };

   int limit = 1000;
   std::vector<date::year_month_day> got = { };
   for(auto d : r1.m_repeat) {
      got.emplace_back(d);
      std::cout << d << "\n";
      if(limit-- < 0)
         break;
   }

   ASSERT_EQ( got, expected );
}

