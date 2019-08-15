#pragma once

#include "bounds.h"
#include <variant>
#include <vector>
#include <date/date.h>

/////////////////////

struct weekly_t {
   int m_count;
   std::vector<date::weekday> m_on_days;
   bounds_t m_bounds;

   struct iterator_t;
   iterator_t begin() const;
   iterator_t end() const;
};

/////////////////////

class weekly_t::iterator_t {
   const weekly_t& m_parent;
   int m_is_end = false;
   int m_number = 0;
   date::year_month_day m_current;
   std::vector<date::days> m_days_offsets;
   decltype(m_days_offsets)::size_type m_current_days_offset_index = 0;

   friend class weekly_t;

   iterator_t(const weekly_t& parent, bool is_end)
      : m_parent(parent)
      , m_is_end(is_end)
   {
      if(!m_is_end)
      {
         const auto&& begin_weekday = date::weekday{date::sys_days{m_parent.m_bounds.m_begin}};
         const auto&& on_days_ = m_parent.m_on_days.empty() ? std::vector<date::weekday>{begin_weekday} : m_parent.m_on_days;

         assert( on_days_.size() >= 1 );

         m_days_offsets.reserve( std::min<decltype(m_days_offsets)::size_type>(on_days_.size(), 7u) );

         auto temp = m_parent.m_bounds.m_begin;
         int initial_offset = 0;
         bool current_already_set = false;
         for(int i = 0; i < 7; ++i) {
            auto p = std::find( on_days_.cbegin(), on_days_.cend(), date::weekday{date::sys_days{temp}} );
            if(p != on_days_.cend()) {

               m_days_offsets.emplace_back( i - initial_offset );

               if(!current_already_set)
               {
                  m_current = temp;
                  current_already_set = true;

                  if(on_days_.size() == 1)
                     break;
               }
               else
               {
               }
            }
            else {
               if(!current_already_set)
                  ++initial_offset;
            }
            
            temp = date::sys_days{temp} + date::days{1};
         }
      }
   }

public:
   iterator_t& operator++() {
      if(!m_is_end) {

         if( std::holds_alternative<int>(m_parent.m_bounds.m_end) && m_number + 1 >= std::get<int>(m_parent.m_bounds.m_end) )
         {
            m_is_end = true;
         }
         else {

            m_current_days_offset_index++;
            if(m_current_days_offset_index < m_days_offsets.size())
            {
               auto&& next = date::sys_days{m_current} + date::days{ m_days_offsets[m_current_days_offset_index] };
               if( (std::holds_alternative<date::year_month_day>(m_parent.m_bounds.m_end) && next > std::get<date::year_month_day>(m_parent.m_bounds.m_end) ) )
               {
                  m_is_end = true;
               }
            }
            else
            {
               m_current_days_offset_index = 0;

               auto&& next = date::sys_days{m_current} + date::weeks{m_parent.m_count};
               if( (std::holds_alternative<date::year_month_day>(m_parent.m_bounds.m_end) && next > std::get<date::year_month_day>(m_parent.m_bounds.m_end) ) )
               {
                  m_is_end = true;
               }
               else {
                  m_current = std::move(next);
               }
            }

            m_number++;
         }
      }

      return *this;
   }

   date::year_month_day operator*() const {
      return date::sys_days{m_current} + date::days{ m_days_offsets[m_current_days_offset_index] };
   }

   date::year_month_day operator*() {
      return date::sys_days{m_current} + date::days{ m_days_offsets[m_current_days_offset_index] };
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

/////////////////////

inline weekly_t::iterator_t weekly_t::begin() const {
   return weekly_t::iterator_t{*this, false};
}

inline weekly_t::iterator_t weekly_t::end() const {
   return weekly_t::iterator_t{*this, true};
}

/////////////////////

