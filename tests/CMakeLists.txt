cmake_minimum_required (VERSION 3.5)

add_executable(daily_test main.cpp daily_test.cpp)
target_link_libraries(daily_test gtest)

add_executable(weekly_test main.cpp weekly_test.cpp)
target_link_libraries(weekly_test gtest)

add_executable(monthly_test main.cpp monthly_test.cpp)
target_link_libraries(monthly_test gtest)

add_executable(yearly_test main.cpp yearly_test.cpp)
target_link_libraries(yearly_test gtest)

add_test(dailyTest daily_test)
add_test(weeklyTest weekly_test)
add_test(monthlyTest monthly_test)
add_test(yearlyTest yearly_test)
