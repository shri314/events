#pragma once

#include "bounds.h"
#include <vector>
#include <optional>
#include <date/date.h>

/////////////////////

struct monthly_by_weekday_t {
   int m_count;
   date::weekday m_on_weekday;
   std::vector<unsigned> m_on_indexes;
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
   std::vector<unsigned> m_offsets;
   decltype(m_offsets)::size_type m_offset_index = 0;

   friend class monthly_by_weekday_t;

   iterator_t(const monthly_by_weekday_t& parent, bool is_end)
      : m_parent(parent)
      , m_is_end(is_end)
   {
      if(!m_is_end)
      {
         const auto& start = m_parent.m_bounds.m_begin;

         m_offsets = [&start, this]() {
            auto offsets = m_parent.m_on_indexes;

            std::sort( offsets.begin(), offsets.end() );
            offsets.erase( std::unique( offsets.begin(), offsets.end() ), offsets.end() );
            offsets.erase( std::remove_if( offsets.begin(), offsets.end(), [](auto x) { return x < 1 && x > 5; }), offsets.end() );

            if(offsets.empty()) {
               const auto& start_weekday_indexed = date::year_month_weekday{start}.weekday_indexed();
               if(start_weekday_indexed.weekday() == m_parent.m_on_weekday) {
                  offsets.emplace_back( start_weekday_indexed.index() );
               }
               else {
                  offsets.emplace_back(1u);
               }
            }

            return offsets;
         }();

         {
            auto&& potential_base = date::year_month{start.year(), start.month()};
            std::optional<unsigned> p_start_index;
            for(decltype(m_offsets.size()) index = 0; index < m_offsets.size(); ++index)
            {
               auto&& next_date = date::year_month_day{potential_base / m_parent.m_on_weekday[m_offsets[index]]};
               if(!next_date.ok()) next_date = date::year_month_day{m_current_base / m_parent.m_on_weekday[date::last]};

               if(next_date < start) {
                  continue;
               }
               else {
                  if(next_date >= start) {
                     p_start_index = index;
                     break;
                  }
               }
            }

            if(p_start_index) {
               m_current_base = potential_base;
               m_offset_index = *p_start_index;
            }
            else {
               m_current_base = potential_base + date::months{1};
               m_offset_index = 0;
            }
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
            auto&& next_date = compute_next(m_current_base, m_parent.m_on_weekday, m_offsets[m_offset_index]);

            if( (std::holds_alternative<date::year_month_day>(m_parent.m_bounds.m_end) && next_date > std::get<date::year_month_day>(m_parent.m_bounds.m_end) ) )
            {
               m_is_end = true;
            }
         }
         else
         {
            m_offset_index = 0;

            auto&& next_base = m_current_base + date::months{m_parent.m_count};
            auto&& next_date = compute_next(next_base, m_parent.m_on_weekday, m_offsets[m_offset_index]);

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
      return compute_next(m_current_base, m_parent.m_on_weekday, m_offsets[m_offset_index]);
   }

   date::year_month_day operator*() {
      return compute_next(m_current_base, m_parent.m_on_weekday, m_offsets[m_offset_index]);
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

private:
   static date::year_month_day compute_next(date::year_month base, date::weekday wd, unsigned wd_index) {
      auto d = date::year_month_day{base / wd[wd_index] };
      if(!d.ok()) d = date::year_month_day{base / wd[date::last]};
      return d;
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

