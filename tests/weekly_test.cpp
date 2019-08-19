#include "rule.h"
#include "test_util.h"

#include <gtest/gtest.h>

#include <vector>
#include <date/date.h>


TEST(weekly_rule, every_week) {

   const std::vector<date::year_month_day> expected = {
      date::day(30)/date::dec/date::year(2019),
      date::day(6)/date::jan/date::year(2020),
      date::day(13)/date::jan/date::year(2020),
   };

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{1,
                     {},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(13)/date::jan/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{1,
                     {},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(19)/date::jan/date::year(2020),  // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{1,
                     {},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        3
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(weekly_rule, every_third_week) {

   const std::vector<date::year_month_day> expected = {
      date::day(30)/date::dec/date::year(2019),
      date::day(20)/date::jan/date::year(2020),
      date::day(10)/date::feb/date::year(2020),
   };

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{3,
                     {},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(10)/date::feb/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{3,
                     {},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(1)/date::mar/date::year(2020),  // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{3,
                     {},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        3
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(weekly_rule, every_week_on_these_days) {

   const std::vector<date::year_month_day> expected = {
      date::day(31)/date::dec/date::year(2019),
      date::day(3)/date::jan/date::year(2020),
      date::day(7)/date::jan/date::year(2020),
      date::day(10)/date::jan/date::year(2020),
      date::day(14)/date::jan/date::year(2020),
      date::day(17)/date::jan/date::year(2020),
   };

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{1,
                     {date::Friday, date::Tuesday},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(17)/date::jan/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{1,
                     {date::Tuesday, date::Friday},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(20)/date::jan/date::year(2020),  // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{1,
                     {date::Friday, date::Tuesday},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        6
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(weekly_rule, every_third_week_on_these_days) {

   const std::vector<date::year_month_day> expected = {
      date::day(31)/date::dec/date::year(2019),
      date::day(3)/date::jan/date::year(2020),
      date::day(21)/date::jan/date::year(2020),
      date::day(24)/date::jan/date::year(2020),
      date::day(11)/date::feb/date::year(2020),
      date::day(14)/date::feb/date::year(2020),
   };

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{3,
                     {date::Friday, date::Tuesday},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(14)/date::feb/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{3,
                     {date::Tuesday, date::Friday},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        date::day(2)/date::mar/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule1_t{
                  title_t{"foo"},
                  weekly_t{3,
                     {date::Friday, date::Tuesday},
                     bounds_t{
                        date::day(30)/date::dec/date::year(2019),
                        6
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}
