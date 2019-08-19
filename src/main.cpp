#include "rule.h"
#include "rule_parser.h"
#include <nlohmann/json.hpp>

#include <date/date.h>
#include <iostream>

/////////////////////

int main() {

   parse_into_rule_t(
      R"(
         {
            "title": "foo",
            "frequency": {
               "value": 2,
               "unit": "days"
            },
            "begins": "2019-11-29",
            "ends": "4"
         }
      )"_json
   );

   // { "title": "Stand up", "frequency": "2 days",                        "begins": "2019-11-29", "ends": "never|date|4" },
   {
      std::cout << "------------------------------------------------------------\n";
      std::cout << " Every other day from 2019-11-29, until 2019-12-05          \n";
      std::cout << "------------------------------------------------------------\n";

      auto r1 = rule_t{
                  title_t{"foo"},
                  daily_t{2,
                     bounds_t{
                        date::day(29)/date::nov/date::year(2019),
                        date::day(5)/date::dec/date::year(2019)
                     }
                  }
      };

      int limit = 10;
      for(auto d : r1) {
         std::cout << d << "\n";
         if(limit-- < 0)
            break;
      }
   }

   // { "title": "Stand up", "frequency": "2 weeks",  "on": "Sat,Sun",     "begins": "2019-11-29", "ends": "never|date|4" },
   {
      std::cout << "------------------------------------------------------------\n";
      std::cout << " Every other week on Mon, Tue from 2019-11-29, until 4 times \n";
      std::cout << "------------------------------------------------------------\n";

      auto r1 = rule_t{
                  title_t{"foo"},
                  weekly_t{2,
                     {date::Monday, date::Tuesday},
                     bounds_t{
                        date::day(29)/date::nov/date::year(2019),
                        4
                     }
                  }
      };

      int limit = 10;
      for(auto d : r1) {
         std::cout << d << "\n";
         if(limit-- < 0)
            break;
      }
   }

   // { "title": "Stand up", "frequency": "1 month", "on": "2, 15",        "begins": "2019-11-29", "ends": "never|date|4" },
   {
      std::cout << "------------------------------------------------------------\n";
      std::cout << " Every other month on 2nd and 15th from 2019-11-29, until 4 times \n";
      std::cout << "------------------------------------------------------------\n";

      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_dates_t{2,
                     {date::day{2}, date::day{15}},
                     bounds_t{
                        date::day(29)/date::nov/date::year(2019),
                        4
                     }
                  }
      };

      int limit = 10;
      for(auto d : r1) {
         std::cout << d << "\n";
         if(limit-- < 0)
            break;
      }
   }

   // { "title": "Stand up", "frequency": "1 year",  "on": "2 Jan, 2 Feb", "begins": "2019-11-29", "ends": "never|date|4" },
   {
      std::cout << "------------------------------------------------------------\n";
      std::cout << " Every other year on 26th Jan and 15th Aug from 2019-11-29, until 4 times \n";
      std::cout << "------------------------------------------------------------\n";

      auto r1 = rule_t{
                  title_t{"foo"},
                  yearly_t{2,
                     {date::jan/date::day{26}, date::aug/date::day{15}},
                     bounds_t{
                        date::day(29)/date::nov/date::year(2019),
                        4
                     }
                  }
      };

      int limit = 10;
      for(auto d : r1) {
         std::cout << d << "\n";
         if(limit-- < 0)
            break;
      }
   }

   // { "title": "Stand up", "frequency": "2 month", "on": "1 Fri",        "begins": "2019-11-29", "ends": "never|date|4" },
   {
      std::cout << "------------------------------------------------------------\n";
      std::cout << " Every other month on 1st friday from 2019-11-29, until 4 times \n";
      std::cout << "------------------------------------------------------------\n";

      auto r1 = rule_t{
                  title_t{"foo"},
                  monthly_by_weekday_t{2,
                     date::Friday[1],
                     bounds_t{
                        date::day(29)/date::nov/date::year(2019),
                        4
                     }
                  }
      };

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
