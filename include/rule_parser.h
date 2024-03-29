#pragma once

#include "rule.h"

#include <nlohmann/json.hpp>

#include <sstream>
#include <stdexcept>
#include <iostream> // debug

namespace detail {
   // trim from start (in place)
   static inline void ltrim(std::string& s) {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](auto ch) { return !std::isspace(ch); }));
   }

   // trim from end (in place)
   static inline void rtrim(std::string& s) {
      s.erase(std::find_if(s.rbegin(), s.rend(), [](auto ch) { return !std::isspace(ch); }).base(), s.end());
   }

   // trim from both ends (in place)
   static inline void trim(std::string& s) {
      ltrim(s);
      rtrim(s);
   }

   static inline void to_lower_case(std::string& s) {
      std::transform(s.begin(), s.end(), s.begin(), [](auto c){ return std::tolower(c); });
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
      detail::to_lower_case(word);
      return (word.size() > 0 && word.back() == 's') ? word.substr(0, word.size() - 1) : word;
   }();

   auto&& extract_ends = [](std::string ends) {

      detail::trim(ends);
      detail::to_lower_case(ends);

      if(ends == "never")
         return bounds_t::end_t{ never_t{} };

      size_t pos;
      int n = stoi(ends, &pos);

      if(pos == ends.size())
         return bounds_t::end_t{ n };

      int y = n;
      ends = ends.substr(pos + 1);
      int m = stoi(ends, &pos);
      ends = ends.substr(pos + 1);
      int d = stoi(ends, &pos);

      return bounds_t::end_t{ date::day(d) / date::month(m) / date::year(y) };
   };

   auto&& extract_begins = [](std::string begins) {

      detail::trim(begins);
      detail::to_lower_case(begins);

      size_t pos;
      int y = stoi(begins, &pos);
      begins = begins.substr(pos + 1);
      int m = stoi(begins, &pos);
      begins = begins.substr(pos + 1);
      int d = stoi(begins, &pos);

      return bounds_t::begin_t{ date::day(d) / date::month(m) / date::year(y) };
   };

   auto&& extract_day_month = [](std::string s_day_month) {

      std::istringstream iss{ s_day_month };
      auto d = [&]() {
         std::string word;
         iss >> word;
         return static_cast<unsigned>( stoi(word) );
      }();

      std::string month;
      iss >> month;
      month = month.substr(0, 3);
      detail::to_lower_case(month);

      if(month == "jan") return date::January / date::day{d};
      else if(month == "feb") return date::February / date::day{d};
      else if(month == "mar") return date::March / date::day{d};
      else if(month == "apr") return date::April / date::day{d};
      else if(month == "may") return date::May / date::day{d};
      else if(month == "jun") return date::June / date::day{d};
      else if(month == "jul") return date::July / date::day{d};
      else if(month == "aug") return date::August / date::day{d};
      else if(month == "sep") return date::September / date::day{d};
      else if(month == "oct") return date::October / date::day{d};
      else if(month == "nov") return date::November / date::day{d};
      else if(month == "dec") return date::December / date::day{d};

      return date::January / date::day{d};
   };

   auto&& extract_weekday = [](std::string s_wd) {
      detail::trim(s_wd);
      s_wd = s_wd.substr(0, 3);
      detail::to_lower_case(s_wd);

      if(s_wd == "sun")      return date::Sunday;
      else if(s_wd == "mon") return date::Monday;
      else if(s_wd == "tue") return date::Tuesday;
      else if(s_wd == "wed") return date::Wednesday;
      else if(s_wd == "thu") return date::Thursday;
      else if(s_wd == "fri") return date::Friday;
      else if(s_wd == "sat") return date::Saturday;

      throw std::runtime_error("bad weekday");
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
      auto&& on_day = rule_json["on_day"];
      if(!on_day.is_null()) {

         std::vector<unsigned> on_indexes;
         for(auto e : rule_json["on"]) {
            on_indexes.emplace_back( std::stoi(std::string(e)) );
         }

         auto r1 = rule_t{
                           title_t{title},
                           monthly_by_weekday_t{
                              frequency_value,
                              extract_weekday(on_day),
                              on_indexes,
                              bounds_t{
                                 extract_begins(begins),
                                 extract_ends(ends)
                              }
                           }
         };

         return r1;
      }
      else {
         std::vector<date::day> on_dates;
         for(auto e : rule_json["on"]) {
            on_dates.emplace_back( std::stoi( std::string(e) ) );
         }

         auto r1 = rule_t{
                           title_t{title},
                           monthly_by_dates_t{
                              frequency_value,
                              on_dates,
                              bounds_t{
                                 extract_begins(begins),
                                 extract_ends(ends)
                              }
                           }
         };

         return r1;
      }
   }
   else if( frequency_unit == "year" )
   {
      auto&& on = rule_json["on"];

      std::vector<date::month_day> on_days;
      for(auto e : on) {

         std::string day_month = e;
         on_days.emplace_back( extract_day_month( day_month ) );
      }

      auto r1 = rule_t{
                        title_t{title},
                        yearly_t{
                           frequency_value,
                           on_days,
                           bounds_t{
                              extract_begins(begins),
                              extract_ends(ends)
                           }
                        }
      };

      return r1;
   }
   else if( frequency_unit == "week" )
   {
      auto&& on = rule_json["on"];

      std::vector<date::weekday> on_days;
      for(auto e : on) {
         on_days.emplace_back( extract_weekday( e ) );
      }

      auto r1 = rule_t{
                        title_t{title},
                        weekly_t{
                           frequency_value,
                           on_days,
                           bounds_t{
                              extract_begins(begins),
                              extract_ends(ends)
                           }
                        }
      };

      return r1;
   }

   throw std::runtime_error("unknown");
}
