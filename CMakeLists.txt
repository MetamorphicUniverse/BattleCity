cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(PROJECT_NAME BattleCity)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)

#Setting something build parameters
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL "Generate installation target" OFF CACHE BOOL "" FORCE)

# 	Adding subdirectory with external librery project. This subdirectori has it's own
# CMakeLists.txt file with project(name), for example: project(GLFW).
add_subdirectory(external/glfw)

# 	Linking external librery to the project. We specify the name of the project and
# the name of the librery that we add.
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)