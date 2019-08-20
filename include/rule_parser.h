#pragma once

#include "rule.h"

#include <nlohmann/json.hpp>

#include <sstream>
#include <iostream> // debug

namespace detail {
   // trim from start (in place)
   static inline void ltrim(std::string &s) {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](auto ch) { return !std::isspace(ch); }));
   }

   // trim from end (in place)
   static inline void rtrim(std::string &s) {
      s.erase(std::find_if(s.rbegin(), s.rend(), [](auto ch) { return !std::isspace(ch); }).base(), s.end());
   }

   // trim from both ends (in place)
   static inline void trim(std::string &s) {
      ltrim(s);
      rtrim(s);
   }
}

rule_t parse_into_rule_t( nlohmann::json rule_json ) {

   std::string title     = rule_json["title"];
   std::string frequency = rule_json["frequency"];
   std::string begins    = rule_json["begins"];
   std::string ends      = rule_json["ends"];

   std::istringstream iss{ frequency };
   auto&& frequency_value = [&]() {
      std::string word;
      iss >> word;
      return std::stoi(word);
   }();

   auto&& frequency_unit = [&]() {
      std::string word;
      iss >> word;
      return (word.size() > 0 && word.back() == 's') ? word.substr(0, word.size() - 1) : word;
   }();

   auto&& extract_ends = [](std::string ends) {

      std::cout << "---------------------\n";
      std::cout << "ends = " << ends << "\n";
      detail::trim(ends);

      if(ends == "never")
         return bounds_t::end_t{ never_t{} };

      size_t pos;
      int n = stoi(ends, &pos);

      std::cout << "ends n = " << n << "\n";

      if(pos == ends.size())
         return bounds_t::end_t{ n };

      int y = n;
      ends = ends.substr(pos + 1);
      int m = stoi(ends, &pos);
      ends = ends.substr(pos + 1);
      int d = stoi(ends, &pos);

      std::cout << "d = " << d << "\n";
      std::cout << "m = " << m << "\n";
      std::cout << "y = " << y << "\n";
      std::cout << "---------------------\n";

      return bounds_t::end_t{ date::day(d) / date::month(m) / date::year(y) };
   };

   auto&& extract_begins = [](std::string begins) {

      std::cout << "---------------------\n";
      std::cout << "begins = " << begins << "\n";
      detail::trim(begins);

      size_t pos;
      int y = stoi(begins, &pos);
      begins = begins.substr(pos + 1);
      int m = stoi(begins, &pos);
      begins = begins.substr(pos + 1);
      int d = stoi(begins, &pos);

      std::cout << "d = " << d << "\n";
      std::cout << "m = " << m << "\n";
      std::cout << "y = " << y << "\n";
      std::cout << "---------------------\n";

      return bounds_t::begin_t{ date::day(d) / date::month(m) / date::year(y) };
   };

   if( frequency_unit == "day" )
   {
      auto r1 = rule_t{
                        title_t{title},
                        daily_t{
                           frequency_value,
                           bounds_t{
                              extract_begins(begins),
                              extract_ends(ends)
                           }
                        }
      };

      return r1;
   }
   else if( frequency_unit == "month" )
   {
      auto&& on = rule_json["on"];

      std::cout << "monthly_by_weekday_t or monthly_by_dates_t rule\n";
      std::cout << "on = " << std::string(on) << "\n";
   }
   else if( frequency_unit == "year" )
   {
      auto&& on = rule_json["on"];

      std::cout << "yearly_t rule\n";
      std::cout << "on = " << std::string(on) << "\n";
   }
   else if( frequency_unit == "week" )
   {
      auto&& on = rule_json["on"];

      std::cout << "weekly_t rule\n";
      std::cout << "on = " << std::string(on) << "\n";
   }
   else
   {
      std::cout << "unknown\n";
   }


   auto r1 = rule_t{
                     title_t{"foo"},
                     daily_t{
                        1,
                        bounds_t{
                           date::day(31)/date::dec/date::year(2222),
                           date::day(1)/date::jan/date::year(2223)
                        }
                     }
   };
   return r1;
}
