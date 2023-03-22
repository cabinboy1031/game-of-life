
set(HEADERS
  ../include/
  ../lib/Unity-2.5.2/src/)

add_executable(gol_grid_test grid_test.c)
target_link_libraries(gol_grid_test ${PROJECT_NAME} unity)   
target_include_directories(gol_grid_test PUBLIC ${HEADERS})
add_test(gol_grid_test grid_test_app)