#pragma once

#include "rule.h"

#include <nlohmann/json.hpp>

#include <iostream> // debug

void parse_into_rule_t( nlohmann::json rule_json ) {

   std::string title = rule_json["title"];
   std::cout << "title = " << title << "\n";

   auto&& frequency = rule_json["frequency"];
   auto&& begins = rule_json["begins"];
   auto&& ends = rule_json["ends"];

   auto&& frequency_value = frequency["value"];
   auto&& frequency_unit = frequency["unit"];

   std::cout << "frequency.value = " << frequency_value << "\n";
   std::cout << "frequency.unit = " << std::string(frequency_unit) << "\n";

   if( frequency_unit == "day" || frequency_unit == "days" )
   {
      std::cout << "daily_t rule\n";
   }
   else if( frequency_unit == "month" || frequency_unit == "months" )
   {
      auto&& on = rule_json["on"];

      std::cout << "monthly_by_weekday_t or monthly_by_dates_t rule\n";
      std::cout << "on = " << std::string(on) << "\n";
   }
   else if( frequency_unit == "year" || frequency_unit == "years" )
   {
      auto&& on = rule_json["on"];

      std::cout << "yearly_t rule\n";
      std::cout << "on = " << std::string(on) << "\n";
   }
   else if( frequency_unit == "week" || frequency_unit == "weeks" )
   {
      auto&& on = rule_json["on"];

      std::cout << "weekly_t rule\n";
      std::cout << "on = " << std::string(on) << "\n";
   }
   else
   {
      std::cout << "unknown\n";
   }

   return;
   std::cout << "begins = " << std::string(begins) << "\n";
   std::cout << "ends = " << std::string(ends) << "\n";
}
