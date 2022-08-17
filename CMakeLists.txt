# Chek for minimum required version of CMake
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

# Create project name variable
set(PROJECT_NAME BattleCity)

# 
project(${PROJECT_NAME})

# Set C++ standard for compilator
set(CMAKE_CXX_STANDARD 17)

# Create a variable with names of sources
set(SOURCES
        src/main.cpp
        src/Renderer/Shader_Program.cpp
		src/Resources/ResourcesManager.cpp
)

# Create a variable with names of headers
set(HEADERS
        src/Renderer/Shader_Program.h
		src/Resources/ResourcesManager.h
)

#  Set CMake building parameters: name.exe sources headers
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

#target_compile_features(${PROJECT_NAME} PUBLIC sxx_std_17)

#set_target_properties(
#        ${PROJECT_NAME} PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
#)

#add_executable(${PROJECT_NAME} src/main.cpp)

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

#add_subdirectory(src)
#link_directories(src)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

