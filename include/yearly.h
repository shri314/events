#pragma once

#include "bounds.h"
#include <vector>
#include <date/date.h>

#include <iostream> // cout

/////////////////////

struct yearly_t {
   int m_count;
   std::vector<date::month_day> m_on_dates;
   bounds_t m_bounds;

   struct iterator_t;
   iterator_t begin() const;
   iterator_t end() const;
};

/////////////////////

class yearly_t::iterator_t {
   const yearly_t& m_parent;
   int m_is_end = false;
   int m_number = 0;

   date::year m_current_base;
   std::vector<date::month_day> m_offsets;
   decltype(m_offsets)::size_type m_offset_index = 0;

   friend class yearly_t;

   iterator_t(const yearly_t& parent, bool is_end)
      : m_parent(parent)
      , m_is_end(is_end)
   {
      if(!m_is_end)
      {
         const auto& start = m_parent.m_bounds.m_begin;
         
         m_offsets = [&start, this]() {
            auto offsets = m_parent.m_on_dates;

            std::sort( offsets.begin(), offsets.end() );
            offsets.erase( std::unique( offsets.begin(), offsets.end() ), offsets.end() );

            if(offsets.empty())
               offsets.emplace_back( date::month_day{start.month(), start.day()} );

            return offsets;
         }();

         auto p = std::lower_bound( m_offsets.begin(), m_offsets.end(), date::month_day{start.month(), start.day()} );
         if(p != m_offsets.end()) {
            m_current_base = start.year();
            m_offset_index = std::distance(m_offsets.begin(), p);
         }
         else {
            m_current_base = start.year() + date::years{1};
            m_offset_index = 0;
         }
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
         m_offset_index++;
         if(m_offset_index < m_offsets.size())
         {
            auto&& next_date = m_current_base / date::month_day{m_offsets[m_offset_index]};
            if(!next_date.ok()) next_date = m_current_base / m_offsets[m_offset_index].month() / date::last;

            if( (std::holds_alternative<date::year_month_day>(m_parent.m_bounds.m_end) && next_date > std::get<date::year_month_day>(m_parent.m_bounds.m_end) ) )
            {
               m_is_end = true;
            }
         }
         else
         {
            m_offset_index = 0;

            auto&& next_base = m_current_base + date::years{m_parent.m_count};
            auto&& next_date = next_base / date::month_day{m_offsets[m_offset_index]};
            if(!next_date.ok()) next_date = next_base / m_offsets[m_offset_index].month() / date::last;

            if( std::holds_alternative<date::year_month_day>(m_parent.m_bounds.m_end) && next_date > std::get<date::year_month_day>(m_parent.m_bounds.m_end) )
            {
               m_is_end = true;
            }
            else
            {
               m_current_base = std::move(next_base);
            }
         }
      }

      if(!m_is_end)
      {
         m_number++;
      }

      return *this;
   }

   date::year_month_day operator*() const {
      auto d = m_current_base / date::month_day{ m_offsets[m_offset_index] };
      return d.ok() ? d : m_current_base / m_offsets[m_offset_index].month() / date::last;
   }

   date::year_month_day operator*() {
      auto d = m_current_base / date::month_day{ m_offsets[m_offset_index] };
      return d.ok() ? d : m_current_base / m_offsets[m_offset_index].month() / date::last;
   }

   bool operator==(const iterator_t& other) const {

      if(m_is_end || other.m_is_end)
         return m_is_end == other.m_is_end;

      return m_number == other.m_number
         && m_current_base == other.m_current_base
         && m_offset_index == other.m_offset_index;
   }

   bool operator!=(const iterator_t& other) const {
      return !(*this == other);
   }
};

/////////////////////

inline yearly_t::iterator_t yearly_t::begin() const {
   return yearly_t::iterator_t{*this, false};
}

inline yearly_t::iterator_t yearly_t::end() const {
   return yearly_t::iterator_t{*this, true};
}

/////////////////////
