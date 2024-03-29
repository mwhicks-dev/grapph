cmake_minimum_required(VERSION 3.26)
project(grapph)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(graph_test include/Graph.h src/Graph.cpp
        src/GraphTest.cpp)
target_link_libraries(graph_test gtest gtest_main)

add_executable(set_func_test include/SetFunctions.h
        src/SetFunctionsTest.cpp)
target_link_libraries(set_func_test gtest gtest_main)

add_executable(homomorphism_test include/Homomorphism.h src/Homomorphism.cpp
        include/Graph.h src/Graph.cpp
        src/HomomorphismTest.cpp)
target_link_libraries(homomorphism_test gtest gtest_main)

add_executable(feature_graph_test include/FeatureGraph.h
        include/Graph.h src/Graph.cpp
        src/FeatureGraphTest.cpp)
target_link_libraries(feature_graph_test gtest gtest_main)
