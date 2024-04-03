cmake_minimum_required(VERSION 3.15)
project(Simple_OpenGL_Scene VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Using GLOB to collect sources is not recommended for new source files as it won't automatically rerun CMake when new files are added.
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Using target_include_directories for specifying include directories
if(APPLE)
    set(GLEW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/dependencies/osx/glew/include")
    set(GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/dependencies/osx/glfw/include")
    set(ASSIMP_PATH "${PROJECT_SOURCE_DIR}/dependencies/osx/assimp/include")
elseif(WIN32)
    set(GLEW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/dependencies/win/glew-2.1.0/include")
    set(GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/dependencies/win/glfw-3.4/include")
    set(ASSIMP_PATH "${PROJECT_SOURCE_DIR}/dependencies/win/assimp/include")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    include
    dependencies/glm/include
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${ASSIMP_PATH}
    dependencies/stb_image/include
)

if(APPLE)
    set(GLEW_PATH "${PROJECT_SOURCE_DIR}/dependencies/osx/glew")
    set(GLFW_PATH "${PROJECT_SOURCE_DIR}/dependencies/osx/glfw")
    set(ASSIMP_PATH "${PROJECT_SOURCE_DIR}/dependencies/osx/assimp")
elseif(WIN32)
    set(GLEW_PATH "${PROJECT_SOURCE_DIR}/dependencies/win/glew-2.1.0")
    set(GLFW_PATH "${PROJECT_SOURCE_DIR}/dependencies/win/glfw-3.4")
    set(ASSIMP_PATH "${PROJECT_SOURCE_DIR}/dependencies/win/assimp")
endif()

find_library(GLEW_LIBRARY NAMES GLEW32 GLEW glew32s PATHS ${GLEW_PATH}/lib NO_DEFAULT_PATH)
find_library(GLFW_LIBRARY NAMES glfw3 glfw PATHS ${GLFW_PATH}/lib NO_DEFAULT_PATH) 

if(WIN32)
    set(ASSIMP_LIBRARY "${ASSIMP_PATH}/lib/assimp-vc143-mt.lib")
endif()


# Linking against the OpenGL framework on macOS
if(APPLE)
    set(OPENGL_LINK "-framework OpenGL")
elseif(WIN32)
    set(OPENGL_LINK opengl32)
endif()

target_link_libraries(${PROJECT_NAME}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${OPENGL_LINK}
)

# Copying the resources folder to the build directory at build time
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)
