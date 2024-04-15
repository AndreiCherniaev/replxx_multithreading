cmake_minimum_required(VERSION 3.14)

project(replxx_multithreading LANGUAGES CXX C DESCRIPTION "replxx in different thread example" VERSION 1.0.0.0)

add_compile_definitions(MYPROJECT_NAME=${PROJECT_NAME})
add_compile_definitions(MYPROJECT_DESCRIPTION=${PROJECT_DESCRIPTION})
add_compile_definitions(CMAKE_PROJECT_VERSION=${CMAKE_PROJECT_VERSION})

include(FetchContent)

FetchContent_Declare(
  replxx
  GIT_REPOSITORY https://github.com/AmokHuginnsson/replxx
  GIT_TAG        master
)
FetchContent_MakeAvailable(replxx)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(${PROJECT_NAME}
  # cxx-api.cxx
  util.c util.h
  include/replxx.hxx

  MainClass.cpp MainClass.h
  main.cpp main.h
  ConsoleWorker.h ConsoleWorker.cpp
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    replxx::replxx
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "27889022+AndreiCherniaev@users.noreply.github.com")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/AndreiCherniaev/replxx_thread")

set(CPACK_SET_DESTDIR true)
set(CPACK_INSTALL_PREFIX bin)

INCLUDE(CPack)
