cmake_minimum_required(VERSION 3.20)
project(LibrarySystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/headers/)

set(ASIO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/asio/asio/include)
set(ASIO_FOUND TRUE)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/SQLiteCpp/)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/crow/)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "headers/*.h")

add_executable(LibrarySystem ${SOURCES} ${HEADERS})

target_link_libraries(LibrarySystem
    SQLiteCpp
    sqlite3
)

target_include_directories(LibrarySystem PRIVATE
    external/crow/include
    ${ASIO_INCLUDE_DIR}
)

if (UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(LibrarySystem
        Threads::Threads  # pthread на UNIX-системах
        dl                # Библиотека dl на UNIX-системах
    )
endif()
