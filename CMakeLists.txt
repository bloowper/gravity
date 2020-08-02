cmake_minimum_required(VERSION 3.16)
project(gravity)

set(CMAKE_CXX_STANDARD 17)
include_directories(obiektyGrawitacyjne keyEventHandling)
add_executable(gravity Game.cpp Game.h Window.h Main.cpp Window.cpp Window.h obiektyGrawitacyjne/ObiektGrawitacyjny.h obiektyGrawitacyjne/ObiektGrawitacyjny.cpp someMethods.cpp someMethods.h keyEventHandling/eventUnit.cpp keyEventHandling/eventUnit.h Game2.cpp obiektyGrawitacyjne/velocity_vector_shape.cpp obiektyGrawitacyjne/velocity_vector_shape.h)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system graphics window network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()