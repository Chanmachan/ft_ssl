# トップレベルのCMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(ft_ssl C)

# コンパイラフラグの設定
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# libftに関する設定
add_subdirectory(libft)

# インクルードディレクトリの設定
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libft/includes
)

# ソースファイルの収集
file(GLOB SSL_SOURCES src/*.c)

# 実行ファイルの設定
add_executable(ft_ssl ${SSL_SOURCES})

# libftとのリンク
target_link_libraries(ft_ssl ft)
