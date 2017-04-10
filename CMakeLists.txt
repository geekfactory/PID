cmake_minimum_required(VERSION 3.6)
project(PID LANGUAGES C VERSION 1.0.0)

add_library(PID STATIC
    PID.c
)

set_target_properties(PID PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
)
