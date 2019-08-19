#include "rule.h"
#include "test_util.h"

#include <gtest/gtest.h>

#include <vector>
#include <date/date.h>


TEST(daily_rule, every_day) {

   const std::vector<date::year_month_day> expected = {
      date::day(29)/date::dec/date::year(2019),
      date::day(30)/date::dec/date::year(2019),
      date::day(31)/date::dec/date::year(2019),
      date::day(1)/date::jan/date::year(2020),
      date::day(2)/date::jan/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  daily_t{1,
                     bounds_t{
                        date::day(29)/date::dec/date::year(2019),
                        date::day(2)/date::jan/date::year(2020)
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  daily_t{1,
                     bounds_t{
                        date::day(29)/date::dec/date::year(2019),
                        5
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(daily_rule, every_third_day) {

   const std::vector<date::year_month_day> expected = {
      date::day(30)/date::dec/date::year(2019),
      date::day(2)/date::jan/date::year(2020),
      date::day(5)/date::jan/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  daily_t{3,
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(5)/date::jan/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  daily_t{3,
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        3
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}
