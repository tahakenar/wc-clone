find_package(GTest REQUIRED)

add_executable(wc_test wc_test.cpp)

target_link_libraries(wc_test
 PRIVATE
  GTest::GTest
  wc_lib)

add_test(wc_gtests wc_test)
