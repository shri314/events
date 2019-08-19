cmake_minimum_required (VERSION 3.10.2)

add_executable(daily_test main.cpp daily_test.cpp)
target_link_libraries(daily_test gtest)

add_executable(weekly_test main.cpp weekly_test.cpp)
target_link_libraries(weekly_test gtest)

add_executable(monthly_by_dates_test main.cpp monthly_by_dates_test.cpp)
target_link_libraries(monthly_by_dates_test gtest)

add_executable(monthly_by_weekday_test main.cpp monthly_by_weekday_test.cpp)
target_link_libraries(monthly_by_weekday_test gtest)

add_executable(yearly_test main.cpp yearly_test.cpp)
target_link_libraries(yearly_test gtest)

add_test(dailyTest daily_test)
add_test(weeklyTest weekly_test)
add_test(monthly_by_datesTest monthly_by_dates_test)
add_test(monthly_by_weekdayTest monthly_by_weekday_test)
add_test(yearlyTest yearly_test)
