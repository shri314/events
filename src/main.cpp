#include "rule.h"
#include "rule_parser.h"
#include <nlohmann/json.hpp>

#include <date/date.h>
#include <iostream>

/////////////////////

int main() {

   auto rules = {
      R"(
         {
            "title": "foo",
            "frequency": "2 days",
            "begins": "2019-11-29",
            "ends": "2019-12-05"
         }
      )",

      R"(
         {
            "title": "foo",
            "frequency": "2 weeks",
            "on": [ "Mon", "Tue" ],
            "begins": "2019-11-29",
            "ends": "4"
         }
      )",

      R"(
         {
            "title": "foo",
            "frequency": "2 months",
            "on": [ "2nd", "15th" ],
            "begins": "2019-11-29",
            "ends": "4"
         }
      )",

      R"(
         {
            "title": "foo",
            "frequency": "2 months",
            "on_the": "1st Fri",
            "begins": "2019-11-29",
            "ends": "4"
         }
      )",

      R"(
         {
            "title": "foo",
            "frequency": "2 year",
            "on": [ "26th Jan", "15th Aug" ],
            "begins": "2019-11-29",
            "ends": "4"
         }
      )",
   };

   for(std::string r : rules)
   {
      std::cout << "------------------------------------------------------------\n";
      std::cout << " " << nlohmann::json::parse(r).dump() << "\n";
      std::cout << "------------------------------------------------------------\n";
      auto r1 = parse_into_rule_t( nlohmann::json::parse(r) );
      int limit = 10;
      for(auto d : r1) {
         std::cout << d << "\n";
         if(limit-- < 0)
            break;
      }
   }

   std::cout << "------------------------------------------------------------\n";
}

/////////////////////
