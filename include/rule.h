#pragma once

#include "daily.h"
#include "weekly.h"
#include "monthly_by_dates.h"
#include <string>

/////////////////////

struct title_t {
   std::string name;
};

/////////////////////

struct rule_t {
   title_t m_name;
   daily_t m_repeat; // FIXME - std::variant< daily_t, yearly_t, ... >
};

struct rule1_t {
   title_t m_name;
   weekly_t m_repeat;
};

struct rule2_t {
   title_t m_name;
   monthly_by_dates_t m_repeat;
};

/////////////////////
