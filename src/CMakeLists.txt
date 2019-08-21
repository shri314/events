cmake_minimum_required (VERSION 3.10.2)

add_executable(
   events-demo
   main.cpp
   ../include/bounds.h
   ../include/daily.h
   ../include/monthly_by_dates.h
   ../include/monthly_by_weekday.h
   ../include/rule.h
   ../include/rule_parser.h
   ../include/weekly.h
   ../include/yearly.h
)

target_link_libraries(
   events-demo
)

