#include "rule.h"

#include <gtest/gtest.h>

#include <vector>
#include <date/date.h>

template<class Rule>
std::vector<date::year_month_day> eval(const Rule& r, int limit, bool print = false) {
   std::vector<date::year_month_day> got = { };
   for(auto d : r.m_repeat) {
      got.emplace_back(d);
      if(print)
         std::cout << d << "\n";
      if(limit-- < 0)
         break;
   }

   return got;
}


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
                  title_t{"Stand up"},
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
                  title_t{"Stand up"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up"},
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


TEST(weekly_rule, every_week) {

   const std::vector<date::year_month_day> expected = {
      date::day(30)/date::dec/date::year(2019),
      date::day(6)/date::jan/date::year(2020),
      date::day(13)/date::jan/date::year(2020),
   };

   {
      auto r1 = rule1_t{
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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
                  title_t{"Stand up every third day"},
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


TEST(monthly_by_dates_rule, every_month_middle) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(15)/date::jan/date::year(2020),
      date::day(15)/date::feb/date::year(2020),
   };

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(15)/date::feb/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(14)/date::mar/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        3
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_dates_rule, every_three_month_middle) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(15)/date::mar/date::year(2020),
      date::day(15)/date::jun/date::year(2020),
   };

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(15)/date::jun/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(14)/date::jul/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        3
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_dates_rule, every_month_endish) {

   const std::vector<date::year_month_day> expected = {
      date::day(31)/date::dec/date::year(2019),
      date::day(31)/date::jan/date::year(2020),
      date::day(29)/date::feb/date::year(2020),
      date::day(31)/date::mar/date::year(2020),
      date::day(30)/date::apr/date::year(2020),
   };

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {},
                     bounds_t{
                        date::day(31)/date::dec/date::year(2019),
                        date::day(30)/date::apr/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {},
                     bounds_t{
                        date::day(31)/date::dec/date::year(2019),
                        date::day(30)/date::may/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {},
                     bounds_t{
                        date::day(31)/date::dec/date::year(2019),
                        5
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_dates_rule, every_three_months_endish) {

   const std::vector<date::year_month_day> expected = {
      date::day(31)/date::dec/date::year(2019),
      date::day(31)/date::mar/date::year(2020),
      date::day(30)/date::jun/date::year(2020),
      date::day(30)/date::sep/date::year(2020),
      date::day(31)/date::dec/date::year(2020),
   };

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {},
                     bounds_t{
                        date::day(31)/date::dec/date::year(2019),
                        date::day(31)/date::dec/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {},
                     bounds_t{
                        date::day(31)/date::dec/date::year(2019),
                        date::day(30)/date::mar/date::year(2021), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {},
                     bounds_t{
                        date::day(31)/date::dec/date::year(2019),
                        5
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_dates_rule, every_month_on_these_days) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(20)/date::dec/date::year(2019),
      date::day(31)/date::dec/date::year(2019),
      date::day(15)/date::jan/date::year(2020),
      date::day(20)/date::jan/date::year(2020),
      date::day(31)/date::jan/date::year(2020),
      date::day(15)/date::feb/date::year(2020),
      date::day(20)/date::feb/date::year(2020),
      date::day(29)/date::feb/date::year(2020),
   };

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {date::day{15}, date::day{20}, date::day{31}},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(29)/date::feb/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {date::day{20}, date::day{31}, date::day{15}}, // different order
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(14)/date::mar/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {date::day{15}, date::day{20}, date::day{31}},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        9
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_dates_rule, every_three_month_on_these_days) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(20)/date::dec/date::year(2019),
      date::day(31)/date::dec/date::year(2019),
      date::day(15)/date::mar/date::year(2020),
      date::day(20)/date::mar/date::year(2020),
      date::day(31)/date::mar/date::year(2020),
      date::day(15)/date::jun/date::year(2020),
      date::day(20)/date::jun/date::year(2020),
      date::day(30)/date::jun/date::year(2020),
   };

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {date::day{15}, date::day{20}, date::day{31}},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(30)/date::jun/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {date::day{20}, date::day{31}, date::day{15}}, // different order
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(14)/date::sep/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {date::day{15}, date::day{20}, date::day{31}},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        9
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_dates_rule, every_month_on_these_days_from_next_month) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::jan/date::year(2020),
      date::day(20)/date::jan/date::year(2020),
      date::day(15)/date::feb/date::year(2020),
      date::day(20)/date::feb/date::year(2020),
      date::day(15)/date::mar/date::year(2020),
      date::day(20)/date::mar/date::year(2020),
   };

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {date::day{15}, date::day{20}},
                     bounds_t{
                        date::day(21)/date::dec/date::year(2019), // begin is beyond current dates
                        date::day(20)/date::mar/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {date::day{20}, date::day{15}}, // different order
                     bounds_t{
                        date::day(21)/date::dec/date::year(2019), // begin is beyond current dates
                        date::day(14)/date::apr/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{1,
                     {date::day{15}, date::day{20}},
                     bounds_t{
                        date::day(21)/date::dec/date::year(2019), // begin is beyond current dates
                        6
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(monthly_by_dates_rule, every_three_month_on_these_days_from_next_month) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::jan/date::year(2020),
      date::day(20)/date::jan/date::year(2020),
      date::day(15)/date::apr/date::year(2020),
      date::day(20)/date::apr/date::year(2020),
      date::day(15)/date::jul/date::year(2020),
      date::day(20)/date::jul/date::year(2020),
   };

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {date::day{15}, date::day{20}},
                     bounds_t{
                        date::day(21)/date::dec/date::year(2019), // begin is beyond current dates
                        date::day(20)/date::jul/date::year(2020),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {date::day{20}, date::day{15}}, // different order
                     bounds_t{
                        date::day(21)/date::dec/date::year(2019), // begin is beyond current dates
                        date::day(14)/date::oct/date::year(2020), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule2_t{
                  title_t{"Stand up every third day"},
                  monthly_by_dates_t{3,
                     {date::day{15}, date::day{20}},
                     bounds_t{
                        date::day(21)/date::dec/date::year(2019), // begin is beyond current dates
                        6
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}
