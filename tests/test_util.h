#pragma once

#include <vector>
#include <date/date.h>
#include <ostream>

template<class Rule>
std::vector<date::year_month_day> eval(const Rule& r, int limit, std::ostream* out = nullptr) {
   std::vector<date::year_month_day> got = { };
   for(auto d : r.m_repeat) {
      got.emplace_back(d);
      if(out)
         *out << d << "\n";
      if(limit-- < 0)
         break;
   }

   return got;
}
