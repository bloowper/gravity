cmake_minimum_required(VERSION 3.16)
project(gravity)

set(CMAKE_CXX_STANDARD 17)
include_directories(TestoweObiekty)
add_executable(gravity Game.cpp Game.h Window.h Main.cpp Window.cpp Window.h TestoweObiekty/ObiektGrawitacyjny.h TestoweObiekty/ObiektGrawitacyjny.cpp TestoweObiekty/someMethods.cpp TestoweObiekty/someMethods.h)


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system graphics window network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()