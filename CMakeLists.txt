cmake_minimum_required(VERSION 3.16)

project(StarryEngine)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_compile_options("/W3;/WX-;/EHsc;/utf-8")
add_compile_options("$<$<CONFIG:DEBUG>:/Zi;/Od;/RTC1;/MDd>")
add_compile_options("$<$<CONFIG:RELEASE>:/O2;/Ob2;/MD;/DNDEBUG>")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libs/WinExport)

add_subdirectory(src/libs/slog)
add_subdirectory(src/editor)

