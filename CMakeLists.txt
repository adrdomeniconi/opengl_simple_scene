cmake_minimum_required(VERSION 3.15)
project(Simple_OpenGL_Scene VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-fdiagnostics-color=always -g)

# Using GLOB to collect sources is not recommended for new source files as it won't automatically rerun CMake when new files are added.
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Using target_include_directories for specifying include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    include
    dependencies/glm/include
    dependencies/glew/2.2.0_1/include
    dependencies/glfw/3.3.9/include
    dependencies/stb_image/include
)

# find_library use relative paths from the project source directory
find_library(GLEW_LIBRARY NAMES GLEW glew32 PATHS ${PROJECT_SOURCE_DIR}/dependencies/glew/2.2.0_1/lib NO_DEFAULT_PATH)
find_library(GLFW_LIBRARY NAMES glfw glfw3 PATHS ${PROJECT_SOURCE_DIR}/dependencies/glfw/3.3.9/lib NO_DEFAULT_PATH)

# Linking against the OpenGL framework on macOS
target_link_libraries(${PROJECT_NAME}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
    "-framework OpenGL"
)

# Copying the resources folder to the build directory at build time
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)
