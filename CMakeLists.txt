cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(NULS)

set (CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED)

include(ExternalProject)
ExternalProject_Add(
    nlohmann_json
    PREFIX "nlohmann"
    URL https://github.com/nlohmann/json/releases/download/v3.5.0/include.zip
    URL_HASH SHA256=3564da9c5b0cf2e032f97c69baedf10ddbc98030c337d0327a215ea72259ea21
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
ExternalProject_Get_property(nlohmann_json SOURCE_DIR)
set(JSON_INCLUDE_DIR ${SOURCE_DIR})

ExternalProject_Add(
    pcg
    PREFIX "pcg"
    URL http://www.pcg-random.org/downloads/pcg-cpp-0.98.zip
    URL_HASH SHA256=de46a88aad4dfe54ef53f66beba56fd0ab3e94aaaa9860cd828b3f1daee13aaf
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
ExternalProject_Get_property(pcg SOURCE_DIR)
set(PCG_INCLUDE_DIR ${SOURCE_DIR}/include)

include_directories(${CMAKE_CURRENT_BINARY_DIR})


file(GLOB_RECURSE sources src/crypto/*.c src/crypto/*.h src/*.cpp src/*.h)
add_library(NULS ${sources} )

target_link_libraries(NULS PRIVATE Boost::boost)
add_dependencies(NULS nlohmann_json pcg)

target_include_directories(NULS
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(tests)
