add_library(cdll STATIC cdll.c)
target_include_directories(cdll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(cdll_tests tests.c)
target_link_libraries(cdll_tests cdll)
