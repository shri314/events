#include <variant>
#include <vector>
#include <string>

#include <date/date.h>

/////////////////////

struct never_t{ };

/////////////////////

struct bounds_t {
   date::year_month_day m_begin;
   std::variant< never_t, date::year_month_day, int > m_end;
};

struct daily_t {
   int m_count;
   bounds_t m_bounds;

   struct iterator_t;
   iterator_t begin();
   iterator_t end();
};

/////////////////////

class daily_t::iterator_t {
   daily_t& m_parent;

   date::year_month_day m_current;
   int m_number = 0;
   int m_is_end = false;

   friend class daily_t;

   iterator_t(daily_t& parent, bool is_end)
      : m_parent(parent)
      , m_current(m_parent.m_bounds.m_begin)
      , m_is_end(is_end)
   {
   }

public:
   iterator_t& operator++() {
      if(!m_is_end) {
         auto&& next = date::sys_days{m_current} + date::days{m_parent.m_count};

         if( (std::holds_alternative<int>(m_parent.m_bounds.m_end) && m_number + 1 > std::get<int>(m_parent.m_bounds.m_end) )
         ||  (std::holds_alternative<date::year_month_day>(m_parent.m_bounds.m_end) && next > std::get<date::year_month_day>(m_parent.m_bounds.m_end)   ) )
         {
            m_is_end = true;
         }
         else
         {
            m_current = std::move(next);
            m_number++;
         }
      }

      return *this;
   }

   date::year_month_day operator*() const {
      return m_current;
   }

   date::year_month_day operator*() {
      return m_current;
   }

   bool operator==(const iterator_t& other) const {

      if(m_is_end || other.m_is_end)
         return m_is_end == other.m_is_end;

      return m_number == other.m_number
         && m_current == other.m_current;
   }

   bool operator!=(const iterator_t& other) const {
      return !(*this == other);
   }
};

daily_t::iterator_t daily_t::begin() {
   return daily_t::iterator_t{*this, false};
}

daily_t::iterator_t daily_t::end() {
   return daily_t::iterator_t{*this, true};
}

/////////////////////

struct title_t {
   std::string name;
};

/////////////////////

struct schedule_rule_t {
   title_t m_name;
   daily_t m_repeat;
};


#include <iostream>
#include <cassert>

int main() {

   /*
      { "name": "Stand up", "repeat": "1 daily",                                "begins": "date", "ends": "never|date|12" },
      { "name": "Stand up", "repeat": "1 weekly",  "repeat_on": "Sat,Sun",      "begins": "date", "ends": "never|date|12" },
      { "name": "Stand up", "repeat": "1 monthly", "repeat_on": "2 Sat",        "begins": "date", "ends": "never|date|12" },
      { "name": "Stand up", "repeat": "1 monthly", "repeat_on": "14, 15",       "begins": "date", "ends": "never|date|12" },
      { "name": "Stand up", "repeat": "1 yearly",  "repeat_on": "2 Jan, 2 Feb", "begins": "date", "ends": "never|date|12" },
   */

   auto r1 = schedule_rule_t{
               title_t{"Stand up"},
               daily_t{1,
                  bounds_t{
                     date::day(29)/date::nov/date::year(2019),
                     date::day(5)/date::dec/date::year(2019)
                  }
               }
   };

   std::vector<date::year_month_day> expected = {
      date::day(29)/date::nov/date::year(2019),
      date::day(30)/date::nov/date::year(2019),
      date::day(1)/date::dec/date::year(2019),
      date::day(2)/date::dec/date::year(2019),
      date::day(3)/date::dec/date::year(2019),
      date::day(4)/date::dec/date::year(2019),
      date::day(5)/date::dec/date::year(2019),
   };

   int limit = 1000;
   std::vector<date::year_month_day> got = { };
   for(auto d : r1.m_repeat) {
      got.emplace_back(d);
      std::cout << d << "\n";
      if(limit-- < 0)
         break;
   }

   assert( got == expected );
}
