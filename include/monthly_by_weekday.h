#pragma once

#include "bounds.h"
#include <vector>
#include <date/date.h>

/////////////////////

struct monthly_by_weekday_t {
   int m_count;
   date::weekday_indexed m_on_date;
   bounds_t m_bounds;

   struct iterator_t;
   iterator_t begin() const;
   iterator_t end() const;
};

/////////////////////

class monthly_by_weekday_t::iterator_t {
   const monthly_by_weekday_t& m_parent;
   int m_is_end = false;
   int m_number = 0;

   date::year_month m_current_base;

   friend class monthly_by_weekday_t;

   iterator_t(const monthly_by_weekday_t& parent, bool is_end)
      : m_parent(parent)
      , m_is_end(is_end)
   {
      if(!m_is_end)
      {
         const auto& start = m_parent.m_bounds.m_begin;
         auto&& potential_base = date::year_month{start.year(), start.month()};
         auto&& next_date = date::year_month_day{potential_base / m_parent.m_on_date};

         if(next_date >= start)
            m_current_base = potential_base;
         else
            m_current_base = potential_base + date::months{1};
      }
   }

public:
   iterator_t& operator++() {
      if(!m_is_end)
      {
         if( std::holds_alternative<int>(m_parent.m_bounds.m_end) && m_number + 1 >= std::get<int>(m_parent.m_bounds.m_end) )
         {
            m_is_end = true;
         }
      }

      if(!m_is_end)
      {
         auto&& next_base = m_current_base + date::months{m_parent.m_count};
         auto&& next_date = date::year_month_day{next_base / m_parent.m_on_date};

         if( std::holds_alternative<date::year_month_day>(m_parent.m_bounds.m_end) && next_date > std::get<date::year_month_day>(m_parent.m_bounds.m_end) )
         {
            m_is_end = true;
         }
         else
         {
            m_current_base = std::move(next_base);
         }
      }

      if(!m_is_end)
      {
         m_number++;
      }

      return *this;
   }

   date::year_month_day operator*() const {
      auto d = date::year_month_day{m_current_base / m_parent.m_on_date};
      return d;
   }

   date::year_month_day operator*() {
      auto d = date::year_month_day{m_current_base / m_parent.m_on_date};
      return d;
   }

   bool operator==(const iterator_t& other) const {

      if(m_is_end || other.m_is_end)
         return m_is_end == other.m_is_end;

      return m_number == other.m_number
         && m_current_base == other.m_current_base;
   }

   bool operator!=(const iterator_t& other) const {
      return !(*this == other);
   }
};

/////////////////////

inline monthly_by_weekday_t::iterator_t monthly_by_weekday_t::begin() const {
   return monthly_by_weekday_t::iterator_t{*this, false};
}

inline monthly_by_weekday_t::iterator_t monthly_by_weekday_t::end() const {
   return monthly_by_weekday_t::iterator_t{*this, true};
}

/////////////////////

