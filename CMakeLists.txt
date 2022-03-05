cmake_minimum_required(VERSION 3.22.2 FATAL_ERROR)

set(PROJECT_NAME SIEngine)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX C)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/Loader/Window.cpp
	src/Loader/Window.h
	src/Loader/GLLoad.cpp
	src/Loader/GLLoad.h
	)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)