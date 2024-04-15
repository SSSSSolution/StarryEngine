cmake_minimum_required(VERSION 3.16)

project(slog)

find_package(spdlog CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED
    include/slog/slog.h
    src/slog.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE STARRY_SLOG_DLL)

add_compile_options(${PROJECT_NAME} PRIVATE "/wd4251")

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE spdlog::spdlog
)


