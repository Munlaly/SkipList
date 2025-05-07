cmake_minimum_required(VERSION 3.31)
project(SkipList C)

set(CMAKE_C_STANDARD 23)

add_executable(SkipList main.c
        skip_list.c
        skip_list.h
        running_competition.c
        running_competition.h
)
