#pragma once

#include "bounds.h"
#include <date/date.h>

/////////////////////

struct daily_t {
   int m_count;
   bounds_t m_bounds;

   struct iterator_t;
   iterator_t begin() const;
   iterator_t end() const;
};

/////////////////////

class daily_t::iterator_t {
   const daily_t& m_parent;
   int m_is_end = false;
   int m_number = 0;

   date::year_month_day m_current_base;

   friend class daily_t;

   iterator_t(const daily_t& parent, bool is_end)
      : m_parent(parent)
      , m_is_end(is_end)
      , m_current_base(m_parent.m_bounds.m_begin)
   {
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
         auto&& next_base = date::sys_days{m_current_base} + date::days{m_parent.m_count};
         auto&& next_date = next_base;

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
      return m_current_base;
   }

   date::year_month_day operator*() {
      return m_current_base;
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

inline daily_t::iterator_t daily_t::begin() const {
   return daily_t::iterator_t{*this, false};
}

inline daily_t::iterator_t daily_t::end() const {
   return daily_t::iterator_t{*this, true};
}

/////////////////////
