add_library(Utilities INTERFACE utilities.h)
target_compile_features(Utilities INTERFACE cxx_std_20)
target_include_directories(Utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})