#include "rule.h"
#include "test_util.h"

#include <gtest/gtest.h>

#include <vector>
#include <date/date.h>


TEST(monthly_by_weekday_rule, every_month_middle_day) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(19)/date::jan/date::year(2020),
      date::day(16)/date::feb/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{1,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(16)/date::feb/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{1,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(14)/date::mar/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{1,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        3
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_weekday_rule, every_three_months_middle_day) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(15)/date::mar/date::year(2020),
      date::day(21)/date::jun/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{3,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(21)/date::jun/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{3,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(19)/date::sep/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{3,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        3
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_weekday_rule, every_three_months_middle_day_from_next_month) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(15)/date::mar/date::year(2020),
      date::day(21)/date::jun/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{3,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(18)/date::nov/date::year(2019),
                        date::day(21)/date::jun/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{3,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(18)/date::nov/date::year(2019),
                        date::day(19)/date::sep/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{3,
                     date::Sunday, {3},
                     bounds_t{
                        date::day(18)/date::nov/date::year(2019),
                        3
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}
