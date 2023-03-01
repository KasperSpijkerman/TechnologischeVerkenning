add_library(circBuffer STATIC circBuffer.cpp)
target_compile_features(circBuffer PRIVATE cxx_std_20)
target_include_directories(circBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})