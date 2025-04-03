cmake_minimum_required(VERSION 3.10)
project(ft C)

# ソースファイルの収集
file(GLOB FT_SOURCES srcs/*.c)

# libftをスタティックライブラリとして構築
add_library(ft STATIC ${FT_SOURCES})

# ライブラリのインクルードディレクトリ
target_include_directories(ft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)