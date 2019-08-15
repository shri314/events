#include "rule.h"
#include "test_util.h"

#include <gtest/gtest.h>

#include <vector>
#include <date/date.h>


TEST(yearly_rule, every_year) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(15)/date::dec/date::year(2020),
      date::day(15)/date::dec/date::year(2021),
   };

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(15)/date::dec/date::year(2021),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(14)/date::dec/date::year(2022), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
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


TEST(yearly_rule, every_three_years) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::dec/date::year(2019),
      date::day(15)/date::dec/date::year(2022),
      date::day(15)/date::dec/date::year(2025),
   };

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(15)/date::dec/date::year(2025),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {},
                     bounds_t{
                        date::day(15)/date::dec/date::year(2019),
                        date::day(14)/date::dec/date::year(2028), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
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


TEST(yearly_rule, every_year_corner) {

   const std::vector<date::year_month_day> expected = {
      date::day(29)/date::feb/date::year(2020),
      date::day(28)/date::feb/date::year(2021),
      date::day(28)/date::feb/date::year(2022),
      date::day(28)/date::feb/date::year(2023),
      date::day(29)/date::feb/date::year(2024),
   };

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {},
                     bounds_t{
                        date::day(29)/date::feb/date::year(2020),
                        date::day(29)/date::feb/date::year(2024),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {},
                     bounds_t{
                        date::day(29)/date::feb/date::year(2020),
                        date::day(27)/date::feb/date::year(2025), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {},
                     bounds_t{
                        date::day(29)/date::feb/date::year(2020),
                        5
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(yearly_rule, every_three_years_corner) {

   const std::vector<date::year_month_day> expected = {
      date::day(29)/date::feb/date::year(2020),
      date::day(28)/date::feb/date::year(2023),
      date::day(28)/date::feb/date::year(2026),
      date::day(28)/date::feb/date::year(2029),
      date::day(29)/date::feb/date::year(2032),
   };

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {},
                     bounds_t{
                        date::day(29)/date::feb/date::year(2020),
                        date::day(29)/date::feb/date::year(2032),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {},
                     bounds_t{
                        date::day(29)/date::feb/date::year(2020),
                        date::day(27)/date::feb/date::year(2035), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {},
                     bounds_t{
                        date::day(29)/date::feb/date::year(2020),
                        5
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(yearly_by_dates_rule, every_year_on_these_days) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::jan/date::year(2019),
      date::day(20)/date::mar/date::year(2019),
      date::day(31)/date::jul/date::year(2019),
      date::day(15)/date::jan/date::year(2020),
      date::day(20)/date::mar/date::year(2020),
      date::day(31)/date::jul/date::year(2020),
      date::day(15)/date::jan/date::year(2021),
      date::day(20)/date::mar/date::year(2021),
      date::day(31)/date::jul/date::year(2021),
   };

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {date::jan/date::day{15}, date::mar/date::day{20}, date::jul/date::day{31}},
                     bounds_t{
                        date::day(15)/date::jan/date::year(2019),
                        date::day(31)/date::jul/date::year(2021),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {date::mar/date::day{20}, date::jul/date::day{31}, date::jan/date::day{15}}, // different order
                     bounds_t{
                        date::day(15)/date::jan/date::year(2019),
                        date::day(14)/date::jan/date::year(2022), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {date::jan/date::day{15}, date::mar/date::day{20}, date::jul/date::day{31}},
                     bounds_t{
                        date::day(15)/date::jan/date::year(2019),
                        9
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(yearly_by_dates_rule, every_three_years_on_these_days) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::jan/date::year(2019),
      date::day(20)/date::mar/date::year(2019),
      date::day(31)/date::jul/date::year(2019),
      date::day(15)/date::jan/date::year(2022),
      date::day(20)/date::mar/date::year(2022),
      date::day(31)/date::jul/date::year(2022),
      date::day(15)/date::jan/date::year(2025),
      date::day(20)/date::mar/date::year(2025),
      date::day(31)/date::jul/date::year(2025),
   };

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {date::jan/date::day{15}, date::mar/date::day{20}, date::jul/date::day{31}},
                     bounds_t{
                        date::day(15)/date::jan/date::year(2019),
                        date::day(31)/date::jul/date::year(2025),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {date::mar/date::day{20}, date::jul/date::day{31}, date::jan/date::day{15}}, // different order
                     bounds_t{
                        date::day(15)/date::jan/date::year(2019),
                        date::day(14)/date::jan/date::year(2028), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {date::jan/date::day{15}, date::mar/date::day{20}, date::jul/date::day{31}},
                     bounds_t{
                        date::day(15)/date::jan/date::year(2019),
                        9
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(yearly_by_dates_rule, every_year_on_these_days_from_next_year) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::jan/date::year(2019),
      date::day(20)/date::mar/date::year(2019),
      date::day(31)/date::jul/date::year(2019),
      date::day(15)/date::jan/date::year(2020),
      date::day(20)/date::mar/date::year(2020),
      date::day(31)/date::jul/date::year(2020),
      date::day(15)/date::jan/date::year(2021),
      date::day(20)/date::mar/date::year(2021),
      date::day(31)/date::jul/date::year(2021),
   };

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {date::jan/date::day{15}, date::mar/date::day{20}, date::jul/date::day{31}},
                     bounds_t{
                        date::day(1)/date::aug/date::year(2018), // begin is beyond current date
                        date::day(31)/date::jul/date::year(2021),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {date::mar/date::day{20}, date::jul/date::day{31}, date::jan/date::day{15}}, // different order
                     bounds_t{
                        date::day(1)/date::aug/date::year(2018), // begin is beyond current date
                        date::day(14)/date::jan/date::year(2022), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{1,
                     {date::jan/date::day{15}, date::mar/date::day{20}, date::jul/date::day{31}},
                     bounds_t{
                        date::day(1)/date::aug/date::year(2018), // begin is beyond current date
                        9
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}


TEST(yearly_by_dates_rule, every_three_years_on_these_days_from_next_year) {

   const std::vector<date::year_month_day> expected = {
      date::day(15)/date::jan/date::year(2019),
      date::day(20)/date::mar/date::year(2019),
      date::day(31)/date::jul/date::year(2019),
      date::day(15)/date::jan/date::year(2022),
      date::day(20)/date::mar/date::year(2022),
      date::day(31)/date::jul/date::year(2022),
      date::day(15)/date::jan/date::year(2025),
      date::day(20)/date::mar/date::year(2025),
      date::day(31)/date::jul/date::year(2025),
   };

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {date::jan/date::day{15}, date::mar/date::day{20}, date::jul/date::day{31}},
                     bounds_t{
                        date::day(1)/date::aug/date::year(2018),
                        date::day(31)/date::jul/date::year(2025),
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {date::mar/date::day{20}, date::jul/date::day{31}, date::jan/date::day{15}}, // different order
                     bounds_t{
                        date::day(1)/date::aug/date::year(2018),
                        date::day(14)/date::jan/date::year(2028), // check upper boundary
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }

   {
      auto r1 = rule3_t{
                  title_t{"Stand up every third day"},
                  yearly_t{3,
                     {date::jan/date::day{15}, date::mar/date::day{20}, date::jul/date::day{31}},
                     bounds_t{
                        date::day(1)/date::aug/date::year(2018),
                        9
                     }
                  }
      };

      ASSERT_EQ( expected, eval(r1, 1000) );
   }
}
