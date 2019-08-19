#pragma once

#include "daily.h"
#include "weekly.h"
#include "monthly_by_dates.h"
#include "monthly_by_weekday.h"
#include "yearly.h"

#include <string>

/////////////////////

struct title_t {
   std::string name;
};

/////////////////////

struct rule_t {
   using repeat_variant_t = std::variant<
      daily_t,
      weekly_t,
      monthly_by_weekday_t,
      monthly_by_dates_t,
      yearly_t
   >;

   using iterator_variant_t = std::variant<
         daily_t::iterator_t,
         weekly_t::iterator_t,
         monthly_by_weekday_t::iterator_t,
         monthly_by_dates_t::iterator_t,
         yearly_t::iterator_t
      >;

   class iterator_t;

   title_t m_name;
   repeat_variant_t m_repeat;

   iterator_t begin() const;
   iterator_t end() const;
};

class rule_t::iterator_t {
   friend class rule_t;
   private:
      iterator_variant_t m_iterator_variant;

   private:
      struct cmp_visitor {
         template<class T>
            auto operator()(T&& left, T&& right) {
               return left == right;
            }

         template<class T, class U>
            auto operator()(T&& left, U&& right) {
               (void)left; (void)right;
               return false;
            }
      };

   public:
      iterator_t( iterator_variant_t&& iterator_variant )
         : m_iterator_variant( std::move(iterator_variant) )
      {
      }

      iterator_t& operator++() {
         std::visit( [](auto&& it) { ++it; }, m_iterator_variant );
         return *this;
      }

      date::year_month_day operator*() const {
         return std::visit( [](auto&& it) { return *it; }, m_iterator_variant );
      }

      date::year_month_day operator*() {
         return std::visit( [](auto&& it) { return *it; }, m_iterator_variant );
      }

      bool operator==(const iterator_t& other) const {
         return std::visit( cmp_visitor{}, m_iterator_variant, other.m_iterator_variant );
      }

      bool operator!=(const iterator_t& other) const {
         return !(*this == other);
      }
};

inline rule_t::iterator_t rule_t::begin() const {
   return std::visit( [](auto&& rep) { return rule_t::iterator_variant_t{ rep.begin() }; }, m_repeat );
}

inline rule_t::iterator_t rule_t::end() const {
   return std::visit( [](auto&& rep) { return rule_t::iterator_variant_t{ rep.end() }; }, m_repeat );
}

/////////////////////
