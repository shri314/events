#include "rule_parser.h"
#include "test_util.h"

#include <gtest/gtest.h>

#include <vector>
#include <date/date.h>


TEST(parser, daily_rule) {

   const std::vector<date::year_month_day> expected = {
      date::day(29)/date::nov/date::year(2019),
      date::day(1)/date::dec/date::year(2019),
      date::day(3)/date::dec/date::year(2019),
      date::day(5)/date::dec/date::year(2019),
   };

   auto r1 = parse_into_rule_t(
      R"(
         {
            "title": "foo",
            "frequency": "2 days",
            "begins": "2019-11-29",
            "ends": "2019-12-05"
         }
      )"_json
   );

   ASSERT_EQ( expected, eval(r1, 1000) );
}


TEST(parser, weekly_rule) {

   const std::vector<date::year_month_day> expected = {
      date::day(2)/date::dec/date::year(2019),
      date::day(3)/date::dec/date::year(2019),
      date::day(16)/date::dec/date::year(2019),
      date::day(17)/date::dec/date::year(2019),
   };

   auto r1 = parse_into_rule_t(
      R"(
         {
            "title": "foo",
            "frequency": "2 weeks",
            "on": [ "Mon", "Tue" ],
            "begins": "2019-11-29",
            "ends": "4"
         }
      )"_json
   );

   ASSERT_EQ( expected, eval(r1, 1000) );
}


TEST(parser, monthly_by_dates_t) {

   const std::vector<date::year_month_day> expected = {
      date::day(2)/date::dec/date::year(2019),
      date::day(15)/date::dec/date::year(2019),
      date::day(2)/date::feb/date::year(2020),
      date::day(15)/date::feb/date::year(2020),
   };

   auto r1 = parse_into_rule_t(
      R"(
         {
            "title": "foo",
            "frequency": "2 months",
            "on": [ "2nd", "15th" ],
            "begins": "2019-11-29",
            "ends": "4"
         }
      )"_json
   );

   ASSERT_EQ( expected, eval(r1, 1000) );
}


TEST(parser, monthly_by_weekday_t) {

   const std::vector<date::year_month_day> expected = {
      date::day(6)/date::dec/date::year(2019),
      date::day(20)/date::dec/date::year(2019),
      date::day(7)/date::feb/date::year(2020),
      date::day(21)/date::feb/date::year(2020),
   };

   auto r1 = parse_into_rule_t(
      R"(
         {
            "title": "foo",
            "frequency": "2 months",
            "on": [ "1st", "3rd" ],
            "on_day": "Fri",
            "begins": "2019-11-29",
            "ends": "4"
         }
      )"_json
   );

   ASSERT_EQ( expected, eval(r1, 1000) );
}


TEST(parser, yearly_rule) {

   const std::vector<date::year_month_day> expected = {
      date::day(26)/date::jan/date::year(2020),
      date::day(15)/date::aug/date::year(2020),
      date::day(26)/date::jan/date::year(2022),
      date::day(15)/date::aug/date::year(2022),
   };

   auto r1 = parse_into_rule_t(
      R"(
         {
            "title": "foo",
            "frequency": "2 year",
            "on": [ "26th Jan", "15th Aug" ],
            "begins": "2019-11-29",
            "ends": "4"
         }
      )"_json
   );

   ASSERT_EQ( expected, eval(r1, 1000) );
}


TEST(parser, yearly_rule_infinite) {

   auto r1 = parse_into_rule_t(
      R"(
         {
            "title": "foo",
            "frequency": "2 year",
            "on": [ "26th Jan", "15th Aug" ],
            "begins": "2019-11-29",
            "ends": "never"
         }
      )"_json
   );

   ASSERT_EQ( 100u, eval(r1, 100).size() );
   ASSERT_EQ( 1000u, eval(r1, 1000).size() );
   ASSERT_EQ( 10000u, eval(r1, 10000).size() );
}
