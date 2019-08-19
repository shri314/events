#include "rule.h"
#include "test_util.h"

#include <gtest/gtest.h>

#include <vector>
#include <date/date.h>


TEST(monthly_by_dates_rule, every_month_middle) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(15)/date::jan/date::year(2020),
      date::day(15)/date::feb/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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


TEST(monthly_by_dates_rule, every_three_months_middle) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(15)/date::mar/date::year(2020),
      date::day(15)/date::jun/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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


TEST(monthly_by_dates_rule, every_month_corner) {

   const std::vector<date::year_month_day> expected = {
      date::day(31)/date::dec/date::year(2019),
      date::day(31)/date::jan/date::year(2020),
      date::day(29)/date::feb/date::year(2020),
      date::day(31)/date::mar/date::year(2020),
      date::day(30)/date::apr/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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


TEST(monthly_by_dates_rule, every_three_months_corner) {

   const std::vector<date::year_month_day> expected = {
      date::day(31)/date::dec/date::year(2019),
      date::day(31)/date::mar/date::year(2020),
      date::day(30)/date::jun/date::year(2020),
      date::day(30)/date::sep/date::year(2020),
      date::day(31)/date::dec/date::year(2020),
   };

   {
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
      auto r1 = rule_t{
                  title_t{"foo"},
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
