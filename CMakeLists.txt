cmake_minimum_required(VERSION 3.22.2 FATAL_ERROR)

set(PROJECT_NAME SIEngine)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX C)

add_executable(${PROJECT_NAME}
	src/main.cpp
	)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)