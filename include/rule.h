#pragma once

#include "daily.h"
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

/////////////////////
