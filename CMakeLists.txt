cmake_minimum_required(VERSION 3.10)
project(MonProjetSFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(app ${SOURCES})

# On ajoute juste une MACRO qui contient le chemin de ton dossier src/shaders
target_compile_definitions(app PRIVATE SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/")
target_compile_definitions(app PRIVATE TEXTURE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/Textures/")

target_link_libraries(app SFML::Graphics SFML::Window SFML::System OpenGL::GL GLEW::GLEW)
target_include_directories(app PUBLIC src)