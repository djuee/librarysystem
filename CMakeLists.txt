cmake_minimum_required(VERSION 3.20)
project(LibrarySystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/headers/)

# Добавляем подмодуль SQLiteCpp
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/SQLiteCpp/)

# Основные исходники
set(SOURCES
    src/Book.cpp
    src/User.cpp
    src/DatabaseManager.cpp
    src/main.cpp
    src/PasswordManager.cpp
    src/Reader.cpp
    src/Admin.cpp
    src/ResearchPaper.cpp
    src/TextBook.cpp
    src/Novel.cpp
)

set(HEADERS
    headers/Book.h
    headers/User.h
    headers/Admin.h
    headers/Reader.h
    headers/PasswordManager.h
    headers/ResearchPaper.h
    headers/TextBook.h
    headers/Novel.h
    headers/DatabaseManager.h
)

# Создаём исполняемый файл
add_executable(LibrarySystem ${SOURCES} ${HEADERS})

# Линкуем SQLiteCpp и SQLite3
target_link_libraries(LibrarySystem
    SQLiteCpp
    sqlite3
)

# Добавляем pthread и dl только на UNIX-системах
if (UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(LibrarySystem
        Threads::Threads  # pthread на UNIX-системах
        dl                # Библиотека dl на UNIX-системах
    )
endif()
