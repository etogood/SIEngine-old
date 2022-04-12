cmake_minimum_required(VERSION 3.21.1 FATAL_ERROR)

set(PROJECT_NAME SIEngine)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX C)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/Loader/Window.cpp
	src/Loader/Window.h
	src/Loader/GLLoad.cpp
	src/Loader/GLLoad.h
	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h
	src/Resources/stb_image.h
	src/Render/ShaderProgram.h
	src/Render/ShaderProgram.cpp
	src/Render/VertexArray.h
	src/Render/VertexArray.cpp
	src/Render/VertexBuffer.h
	src/Render/VertexBuffer.cpp
	src/Render/IndexBuffer.cpp
	src/Render/IndexBuffer.h
	src/Render/VertexBufferLayout.cpp
	src/Render/VertexBufferLayout.h
	src/Render/Objects/Scene.cpp
	src/Render/Objects/Scene.h
	src/Render/Objects/Sprite.cpp
	src/Render/Objects/Sprite.h
	src/Render/Texture2D.cpp
	src/Render/Texture2D.h
	src/Render/Objects/Cube.h
	src/Render/Objects/Cube.cpp
		src/Render/Objects/NullObject.cpp src/Render/Objects/NullObject.h)

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

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)